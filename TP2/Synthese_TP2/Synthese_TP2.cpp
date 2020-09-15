
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
    image.create(width, height);

    // Sphere data
    glm::vec3 center(0, 0, 10);
    glm::float32 radius = 50;

    // Ray direction
    glm::vec3 direction(0, 0, 1); //normalized value !

    // Compute pixel color
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; y++){
            // Ray origin
            glm::vec3 origin(x - width/2, y - height/2, 0);
            glm::vec3 position;
            glm::vec3 normal;
            if (glm::intersectRaySphere(origin, direction, center, radius, position, normal)) {
                image.setPixel(x, y, sf::Color::Green);
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