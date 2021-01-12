

#include "Scene.h"

#define _USE_MATH_DEFINES
#include <math.h>

Scene::Scene(unsigned int width, unsigned int height, std::shared_ptr<Camera> camera, const color3 &backgroundColor)
    : m_width(width), m_height(height), m_camera(camera), m_backgroundColor(backgroundColor),
      m_gen(757617000), m_disPosition(0.0f, std::nextafter(1000.0f, DBL_MAX)),
      m_disSize(1.0f, std::nextafter(30.0f, DBL_MAX)), m_disOffsetRay(-1.0f, std::nextafter(1.0f, DBL_MAX))
{}

Scene::~Scene() {}


void Scene::createScene(unsigned int nbGenerated) {
    m_lightList.emplace_back(glm::vec3(-900, -900, 700), color3(1000000, 0, 0));
    m_lightList.emplace_back(glm::vec3(0, -800, 0), color3(1000000, 1000000, 1000000));
    m_lightList.emplace_back(glm::vec3(500, 500, 0), color3(0, 1000000, 500000));

    //Up
    m_backgroundObjectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(color3(0.1f, 0.1f, 0.1f), SceneObjectType::DIFFUSE, glm::vec3(0, -100500.0f - m_height / 2.0f, 500.0f), 100000.0f)));

    //Down
    m_backgroundObjectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(color3(0.3f, 0.3f, 0.3f), SceneObjectType::DIFFUSE, glm::vec3(100500.0f + m_width / 2.0f, 0, 500.0f), 100000.0f)));

    //Left
    m_backgroundObjectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(color3(0.5f, 0.5f, 0.5f), SceneObjectType::DIFFUSE, glm::vec3(-100500.0f - m_width / 2.0f, 0, 500.0f), 100000.0f)));

    //Right
    m_backgroundObjectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(color3(0.7f, 0.7f, 0.7f), SceneObjectType::DIFFUSE, glm::vec3(0, 100500.0f + m_height / 2.0f, 500.0f), 100000.0f)));

    //Back
    m_backgroundObjectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(color3(0.9f, 0.9f, 0.9f), SceneObjectType::DIFFUSE, glm::vec3(0, 0, 101000.0f), 100000.0f)));


    m_objectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(color3(0, 1, 1), SceneObjectType::REFLECTIVE, glm::vec3(0, 0, 200), 100)));
    m_objectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(color3(1, 1, 0), SceneObjectType::REFLECTIVE, glm::vec3(100, 200, 400), 150)));
    m_objectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(color3(1, 0, 1), SceneObjectType::REFLECTIVE, glm::vec3(-300, -300, 800), 200)));

    generateSphere(nbGenerated);
}

void Scene::generateSphere(unsigned int nb) {

    for (unsigned int i = 0; i < nb; i++) {
        glm::vec3 position(m_disPosition(m_gen)-500.0f, m_disPosition(m_gen)-500.0f, m_disPosition(m_gen)); //[0, 1000] * 3

        //float size = m_disSize(m_gen); // [1.0f, 30.0f]
        float size = 15.0f;
        color3 color(0.3f, 0, 0.5f); // [0; 1] * 3

        m_objectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(color, SceneObjectType::DIFFUSE, position, size)));
    }

}

void Scene::buildStructure() {
    m_BVHroot = std::make_unique<BVHNode>(BVHNode::createBVHNode(m_objectList));
}

void Scene::renderImage(const std::string &fileName, unsigned int nbCastPerPixel, unsigned int maxDepth) {

    std::vector<std::vector<color3>> pixels(m_width, std::vector<color3>(m_height, color3(0, 0, 0)));

    // Compute pixel color
    // Also retrieves the max value on each color component

    // For each pixel
    for (unsigned int x = 0; x < m_width; ++x) {
        for (unsigned int y = 0; y < m_height; y++){

            // Setting value to 0 to avoid undefined behaviors
            pixels[x][y] = color3(0, 0, 0);

            // Send nbCastPerPixel randomly distrubuted around the pixel itself
            for (unsigned int i = 0; i < nbCastPerPixel; i++){

                Ray ray = m_camera->getRay(x, y);

                // Get offset in range [-1.0f, 1.0f] for BOTH X and Y coordinates
                // Add both offset to corresponding coordinate in the origin
                float offsetX = m_disOffsetRay(m_gen);
                float offsetY = m_disOffsetRay(m_gen);

                ray.m_origin.x += offsetX;
                ray.m_origin.y += offsetY;

                pixels[x][y] += rayTracePixel(ray, maxDepth);
            }

            pixels[x][y] /= nbCastPerPixel;

        }
    }

    createImage(fileName, pixels);
}


color3 Scene::rayTracePixel(const Ray &ray, unsigned int depth) {

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
            if (depth == 0){
                pixelColor += computeDiffuseObject(position, normal, intersectedObject.value());
            }else{
                pixelColor += computeReflectiveObject(position, normal, intersectedObject.value(), ray, depth);
            }
            break;
    }


    return pixelColor;
}

color3 Scene::computeReflectiveObject(const glm::vec3 &position, const glm::vec3 &normal, const std::shared_ptr<SceneObject> &object, const Ray &ray, unsigned int bounceCounter) {
    
    // Get reflective Direction
    // With this, construct new ray
    // And return rayTracePixel(ray);

    glm::vec3 reflectiveDirection = glm::dot(-ray.m_direction, normal) * normal * 2.0f + ray.m_direction;

    const Ray nextRay(position, reflectiveDirection);

    return rayTracePixel(nextRay, bounceCounter - 1) * object->m_albedo;

}

color3 Scene::computeDiffuseObject(const glm::vec3 &position, const glm::vec3 &normal, const std::shared_ptr<SceneObject> &object) {  
    //return object->m_albedo;

    glm::vec3 positionLightIntersected;
    glm::vec3 normalLightIntersected;

    color3 colorLighted(0, 0, 0);
    // Should I count the number of element ?
    // And divide by it ?

    for (auto &light : m_lightList) {

        const Ray toLightRay = light.getRayFrom(position);

        if (!lightIntersection(position, light, toLightRay, positionLightIntersected, normalLightIntersected)) {
            colorLighted += calculateIntensity(position, normal, light, toLightRay, object->m_albedo);
        }

    }

    return colorLighted;
}


color3 Scene::calculateIntensity(const glm::vec3 &position, const glm::vec3 &normal, const Light &light, const Ray &toLightRay, const color3 &albedo) {
    float cosT = glm::dot(normal, toLightRay.m_direction);
    float dist2 = glm::distance2(position, light.m_position);
    return cosT * light.m_color * albedo / (dist2 * (float)M_PI);
}


bool Scene::lightIntersection(const glm::vec3 &position, const Light &light, const Ray &toLightRay, glm::vec3 &positionLightIntersected, glm::vec3 &normalLightIntersected) {
    // Guard for empty list
    if (m_objectList.size() == 0) {
        return false;
    }

    float t;
    float distMax2 = glm::distance2(position, light.m_position);

    for (auto &object : m_objectList) {
        if (object->intersect(toLightRay, positionLightIntersected, normalLightIntersected, t)) {
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
    float t = std::numeric_limits<float>::infinity();

    if (m_BVHroot) {

        std::optional<std::shared_ptr<SceneObject>> closestFromBVH = m_BVHroot->findClosestIntersection(ray, position, normal, t);

        if (closestFromBVH) {
            closestObject = closestFromBVH.value();
        }

        //Find the closest one from the other list
        tnear = t;
    }
    else
    {
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
    }

    for (auto &object : m_backgroundObjectList) {
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