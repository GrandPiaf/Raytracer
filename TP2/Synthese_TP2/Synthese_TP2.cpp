
#include <iostream>

#include "Synthese_TP2.h"

#include "glm/glm.hpp"
#include "glm/gtx/intersect.hpp"
#include "SFML/Graphics.hpp"

using namespace std;

int main()
{

    unsigned int width = 800;
    unsigned int height = 600;

    // Create image
    sf::Image image;
    image.create(width, height, sf::Color::Magenta);

    // Sphere data
    glm::vec3 center(0, 0, 10);
    glm::float32 radius = 100;

    // Ray direction
    glm::vec3 direction(0, 0, 1); //normalized value !

    // Light position
    glm::vec3 light(0, 10, 10);

    // Compute pixel color
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; y++){
            
            // Ray origin
            glm::vec3 origin(static_cast<float>(x) - width / 2, static_cast<float>(y) - height / 2, 0);
            glm::vec3 position;
            glm::vec3 normal;

            // If false, no intersection found
            if (glm::intersectRaySphere(origin, direction, center, radius, position, normal)) {

                // Compute light intersection
                glm::vec3 positionDecalee = position + 0.1f * normal;
                glm::vec3 lightDirection = light - position;
                glm::normalize(lightDirection);
                glm::vec3 secondPosition;
                glm::vec3 secondNormal;
                if (glm::intersectRaySphere(positionDecalee, lightDirection, center, radius, secondPosition, secondNormal)) {
                    image.setPixel(x, y, sf::Color::Green);
                }
                else {
                    image.setPixel(x, y, sf::Color::Yellow);
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