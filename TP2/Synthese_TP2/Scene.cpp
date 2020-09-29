#include "Scene.h"

Scene::Scene(unsigned int width, unsigned int height, std::shared_ptr<Camera> camera, const sf::Color &backgroundColor) : m_width(width), m_height(height), m_camera(camera), m_backgroundColor(backgroundColor) {}

Scene::~Scene()
{
}

void Scene::renderImage(const std::string &fileName) {

    Light redLight(glm::vec3(-200, -200, 300), glm::vec3(1000, 100, 42)); //Red light
    m_lightList.emplace_back(redLight);

    m_objectList.emplace_back( std::shared_ptr<SceneObject>(new Sphere(sf::Color::Green, glm::vec3(0, 0, 200), 100)) );
    m_objectList.emplace_back(std::shared_ptr<SceneObject>(new Sphere(sf::Color::Yellow, glm::vec3(100, 200, 400), 100)));

    std::vector<std::vector<sf::Color>> pixels(m_width, std::vector<sf::Color>(m_height, m_backgroundColor));

    // Compute pixel color
    for (unsigned int x = 0; x < m_width; ++x) {
        for (unsigned int y = 0; y < m_height; y++){
            Ray ray = m_camera->getRay(x, y);
            pixels[x][y] = rayTracePixel(ray);
        }
    }

    createImage("../../../result.png", pixels);
}


void Scene::createImage(std::string path, std::vector<std::vector<sf::Color>> pixels) {
    m_image.create(m_width, m_height);

    for (unsigned int x = 0; x < m_width; ++x) {
        for (unsigned int y = 0; y < m_height; y++) {
            m_image.setPixel(x, y, pixels[x][y]);
        }
    }

    m_image.saveToFile(path);
}



sf::Color Scene::rayTracePixel(const Ray &ray) {

    /*
        - Calculer l'intersection de tout les objets et retourner l'objet le plus proche avec son point d'intersection et sa normale (Quelle est l'intersection la plus proche)
        Donc calculer l'intersection de tout les objets ET garder celui avec le t le plus petit
    
        - Pour chaque lumi�re, calculer si l'intersection trouv�e pr�c�demment est occult�.
        - Calculer la lumi�re, etc ...
    
    */

    glm::vec3 position;
    glm::vec3 normal;

    std::optional<std::shared_ptr<SceneObject>> intersectedObject = findClosestIntersection(ray, position, normal);
    
    // No object intersected
    if (!intersectedObject) {
        return m_backgroundColor;
    }


    glm::vec3 positionLight;
    glm::vec3 normalLight;


    for (auto &light : m_lightList) {

        Ray toLight = light.getRayFrom(position);

        for (auto& object2 : m_objectList) {
            
            float osef;

            if (object2->intersect(toLight, positionLight, normalLight, osef)) {

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