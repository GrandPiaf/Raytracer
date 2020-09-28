#include "Scene.h"

Scene::Scene(unsigned int width, unsigned int height, std::shared_ptr<Camera> camera, const sf::Color &backgroundColor) : m_width(width), m_height(height), m_camera(camera), m_backgroundColor(backgroundColor)
{
    m_image.create(m_width, m_height, m_backgroundColor);
}

Scene::~Scene()
{
}

void Scene::renderImage(const std::string &fileName) {

    Light redLight(glm::vec3(-200, -200, 300), glm::vec3(1000, 100, 42)); //Red light
    m_lightList.emplace_back(redLight);

    m_objectList.emplace_back( std::shared_ptr<SceneObject>(new Sphere(sf::Color::Green, glm::vec3(0, 0, 200), 100)) );
    m_objectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(sf::Color::Yellow, glm::vec3(100, 200, 400), 100)));



    // Compute pixel color
    for (unsigned int x = 0; x < m_width; ++x) {
        for (unsigned int y = 0; y < m_height; y++){

            /*
            Ray should be compute from Camera
            Depending on Camera type : orthogonal or percpestive
            */

            Ray ray = m_camera->getRay(x, y);

            //glm::vec3 origin(static_cast<float>(x) - m_width / 2, static_cast<float>(y) - m_height / 2, 0);
            //Ray ray(origin, m_camera.m_direction);

            m_image.setPixel(x, y, rayTracePixel(ray));

        }
    }


    m_image.saveToFile("../../../result.png");
}


sf::Color Scene::rayTracePixel(const Ray &ray) {

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

    //return intersectedObject.value()->m_color;


    glm::vec3 positionLight;
    glm::vec3 normalLight;

    position += normal;

    for (auto &light : m_lightList) {

        Ray toLight = light.getRayFrom(position);

        for (auto& object2 : m_objectList) {

            if (object2->intersect(toLight, positionLight, normalLight)) {

                return sf::Color::Black;
                        
            }
        }
    }

    return intersectedObject.value()->m_color;
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
        if (object->intersect(ray, positionTemp, normalTemp)) {
            
            t = glm::distance2(ray.m_origin, positionTemp);

            // We intersect a closer object
            if (t < tnear) {
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