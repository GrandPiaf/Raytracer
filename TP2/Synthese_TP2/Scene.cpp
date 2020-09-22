#include "Scene.h"

Scene::Scene(unsigned int width, unsigned int height, const Camera &camera, const sf::Color &backgroundColor) : m_width(width), m_height(height), m_camera(camera), m_backgroundColor(backgroundColor)
{
    m_image.create(m_width, m_height, m_backgroundColor);
}

Scene::~Scene()
{
}

void Scene::renderImage(const std::string &fileName) {

    Light redLight(glm::vec3(400, 400, 200), glm::vec3(1000, 100, 42)); //Red light
    m_lightList.push_back(redLight);



    //std::unique_ptr<SceneObject> s(new Sphere(glm::vec3(0, 0, 10), 100));
    m_objectList.push_back( std::unique_ptr<SceneObject>(new Sphere(glm::vec3(0, 0, 10), 100)) );

    //SceneObject* s2 = new Sphere(glm::vec3(40, 40, 10), 100);
    //objectsList.push_back(s2);


    // Compute pixel color
    for (unsigned int x = 0; x < m_width; ++x) {
        for (unsigned int y = 0; y < m_height; y++){

            m_image.setPixel(x, y, rayTracePixel(x, y));

        }
    }


    m_image.saveToFile("../../../result.png");
}


sf::Color Scene::rayTracePixel(unsigned int x, unsigned int y) {

    /*
        - Calculer l'intersection de tout les objets et retourner l'objet le plus proche avec son point d'intersection et sa normale (Quelle est l'intersection la plus proche)
        Donc calculer l'intersection de tout les objets ET garder celui avec le t le plus petit
    
        - Pour chaque lumière, calculer si l'intersection trouvée précédemment est occulté.
        - Calculer la lumière, etc ...
    
    */


    // Ray origin
    glm::vec3 origin(static_cast<float>(x) - m_width / 2, static_cast<float>(y) - m_height / 2, 0);
    Ray pixel(origin, m_camera.m_direction);

    glm::vec3 position;
    glm::vec3 normal;

    // access by reference to avoid copying
    for (auto& object : m_objectList) {

        // If false, no intersection found
        if (object->intersect(pixel, position, normal)) {

            glm::vec3 positionLight, normalLight;

            for (auto& light : m_lightList) {

                Ray toLight = light.getRayFrom(position);

                for (auto& object2 : m_objectList) {

                    if (object2->intersect(toLight, positionLight, normalLight)) {

                        return sf::Color::Green;
                    
                    } else {
                    
                        return sf::Color::Black;
                    
                    }
                }
            }

        }
    }

    return m_backgroundColor;
}

const sf::Image Scene::getImage() {
    return m_image;
}