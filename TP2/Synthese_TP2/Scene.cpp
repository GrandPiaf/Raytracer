

#include "Scene.h"

#define _USE_MATH_DEFINES
#include <math.h>

Scene::Scene(unsigned int width, unsigned int height, std::shared_ptr<Camera> camera, const color3 &backgroundColor) : m_width(width), m_height(height), m_camera(camera), m_backgroundColor(backgroundColor) {}

Scene::~Scene() {}

void Scene::renderImage(const std::string &fileName) {

    //Red light
    Light redLight(glm::vec3(-200, -200, 300), color3(1000000, 1000000, 1000000));
    m_lightList.emplace_back(redLight);

    m_objectList.emplace_back( std::shared_ptr<SceneObject>( new Sphere( color3(0, 1, 1), SceneObjectType::DIFFUSE, glm::vec3(0, 0, 200), 100) ) );
    m_objectList.emplace_back( std::shared_ptr<SceneObject>( new Sphere( color3(1, 1, 0), SceneObjectType::DIFFUSE, glm::vec3(100, 200, 400), 100) ) );

    std::vector<std::vector<color3>> pixels(m_width, std::vector<color3>(m_height, color3(0, 0, 0)));

    // Compute pixel color
    // Also retrieves the max value on each color component
    for (unsigned int x = 0; x < m_width; ++x) {
        for (unsigned int y = 0; y < m_height; y++){
            Ray ray = m_camera->getRay(x, y);
            pixels[x][y] = rayTracePixel(ray);
        }
    }

    createImage("../../../result.png", pixels);
}


color3 Scene::rayTracePixel(const Ray &ray) {

    /*
        - Calculer l'intersection de tout les objets et retourner l'objet le plus proche avec son point d'intersection et sa normale (Quelle est l'intersection la plus proche)
        Donc calculer l'intersection de tout les objets ET garder celui avec le t le plus petit
    
        - Pour chaque lumière, calculer si l'intersection trouvée précédemment est occulté.
        - Calculer la lumière, etc ...
    
    */

    glm::vec3 position;
    glm::vec3 normal;

    std::optional<std::shared_ptr<SceneObject>> intersectedObject = findClosestIntersection(ray, position, normal);
    
    // No object intersected
    if (!intersectedObject) {
        return m_backgroundColor;
    }

    color3 pixelColor(0, 0, 0);

    switch (intersectedObject.value()->m_type)
    {
        case SceneObjectType::DIFFUSE:

            pixelColor += computeDiffuseObject(position, normal, intersectedObject.value());

            break;
        case SceneObjectType::REFLECTIVE:
            break;
        default:
            break;
    }


    return pixelColor;
}

color3 Scene::computeDiffuseObject(const glm::vec3 &position, const glm::vec3 &normal, const std::shared_ptr<SceneObject> &object) {
    glm::vec3 positionLightIntersected;
    glm::vec3 normalLightIntersected;

    color3 colorLighted(0, 0, 0);
    // Should I count the number of element ?
    // And divide by it ?

    for (auto &light : m_lightList) {

        Ray toLightRay = light.getRayFrom(position);

        if (!lightIntersection(position, light, positionLightIntersected, normalLightIntersected)) {
            colorLighted += CalculateIntensity(position, normal, light, toLightRay, object->m_albedo);
        }

    }

    return colorLighted;
}


color3 Scene::CalculateIntensity(const glm::vec3 &position, const glm::vec3 &normal, const Light &light, const Ray &toLightRay, const color3 &albedo) {
    float cosT = glm::dot(normal, toLightRay.m_direction);
    float dist2 = glm::distance2(position, light.m_position);
    return cosT * light.m_color * albedo / (dist2 * (float)M_PI);
}


bool Scene::lightIntersection(const glm::vec3 &position, const Light &light, glm::vec3 &positionLightIntersected, glm::vec3 &normalLightIntersected) {
    // Guard for empty list
    if (m_objectList.size() == 0) {
        return false;
    }

    Ray ray(light.m_position, (light.m_position - position));
    float t;

    float distMax2 = glm::distance2(position, light.m_position);

    for (auto &object : m_objectList) {
        if (object->intersect(ray, positionLightIntersected, normalLightIntersected, t)) {
            float currDist2 = glm::distance2(position, positionLightIntersected);

            // If object is intersected BETWEEN position and light position
                // return true;
            if (currDist2 < distMax2) {
                return true;
            }
        }
    }

    // If we reach here, nothing was hit between position and light position
    return false;
}

std::optional<std::shared_ptr<SceneObject>> Scene::findClosestIntersection(const Ray &ray, glm::vec3 &position, glm::vec3 &normal) {

    // Guard for empty list
    if (m_objectList.size() == 0) {
        return std::nullopt;
    }

    // Object to return (if intersected)
    std::shared_ptr<SceneObject> closestObject;
    glm::vec3 positionTemp;
    glm::vec3 normalTemp;

    float tnear = std::numeric_limits<float>::infinity();

    float t;
    // access by reference to avoid copying
    for (auto &object : m_objectList) {
        if (object->intersect(ray, positionTemp, normalTemp, t)) {

            // We intersect a closer object
            if (t <= tnear) {
                tnear = t;
                closestObject = object;
                position = positionTemp;
                normal = normalTemp;
            }

        }
    }

    // No object intersected
    if(tnear == std::numeric_limits<float>::infinity()){
        return std::nullopt;
    }

    return { closestObject };
}



const sf::Image &Scene::getImage() const {
    return m_image;
}

void Scene::createImage(std::string path, std::vector<std::vector<color3>> pixels) {
    m_image.create(m_width, m_height);

    for (unsigned int x = 0; x < m_width; ++x) {
        for (unsigned int y = 0; y < m_height; y++) {
            m_image.setPixel(x, y, convertPixel(pixels[x][y]));
        }
    }

    m_image.saveToFile(path);
}

sf::Color Scene::convertPixel(color3 &p) {

    float maxIntensity = 2.0f;

    return sf::Color(
        std::clamp((int)(std::powf(p.r, 1 / 2.2) * 255.0f / maxIntensity), 0, 255),
        std::clamp((int)(std::powf(p.g, 1 / 2.2) * 255.0f / maxIntensity), 0, 255),
        std::clamp((int)(std::powf(p.b, 1 / 2.2) * 255.0f / maxIntensity), 0, 255)
    );
}
//
//template <typename T>
//T changeRange(T const &OldValue, T const &OldMin, T const &OldMax, T const &NewMin, T const &NewMax) {
//    T OldRange = (OldMax - OldMin);
//    T NewRange = (NewMax - NewMin);
//    T NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin;
//    return NewValue;
//}