
#include <iostream>

#include "Synthese_TP2.h"

using namespace std;

int main()
{

    unsigned int width = 800;
    unsigned int height = 600;

    // Create image
    sf::Image image;
    image.create(width, height, sf::Color(255, 255, 255, 10));



    // Ray direction
    glm::vec3 direction(0, 0, 1); //normalized value !


    std::vector<Light> lightList;

    Light redLight(glm::vec3(400, 400, 200), glm::vec3(1000, 100, 42)); //Red light
    lightList.push_back(redLight);


    // List of objects in our scene
    std::vector<SceneObject*> objectList;

    SceneObject* s = new Sphere(glm::vec3(0, 0, 10), 100);
    objectList.push_back(s);

    //SceneObject* s2 = new Sphere(glm::vec3(40, 40, 10), 100);
    //objectsList.push_back(s2);


    // Compute pixel color
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; y++){
            
            // Ray origin
            glm::vec3 origin(static_cast<float>(x) - width / 2, static_cast<float>(y) - height / 2, 0);
            Ray pixel(origin, direction);

            glm::vec3 position;
            glm::vec3 normal;

            // access by reference to avoid copying
            for (auto& object : objectList) {
            
                // If false, no intersection found
                if (object->intersect(pixel, position, normal)) {

                    glm::vec3 positionLight, normalLight;

                    for (auto& light : lightList) {
                        
                        Ray toLight = light.getRayFrom(position);

                        for (auto& object2 : objectList) {

                            if (object2->intersect(toLight, positionLight, normalLight)) {
                                image.setPixel(x, y, sf::Color::Green);
                            }
                        }
                    }
            
                }
            }

        }
    }


    image.saveToFile("../../../result.png");
}

template <typename T>
T changeRange(T const& OldValue, T const& OldMin, T const& OldMax, T const& NewMin, T const& NewMax) {
    T OldRange = (OldMax - OldMin);
    T NewRange = (NewMax - NewMin);
    T NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin;
    return NewValue;
}