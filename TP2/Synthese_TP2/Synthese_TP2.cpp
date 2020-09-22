
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <SFML/Graphics.hpp>

#include "Synthese_TP2.h"
#include "Ray.h"
#include "SceneObject.h"
#include "Sphere.h"

using namespace std;

int main()
{

    unsigned int width = 800;
    unsigned int height = 600;

    // Create image
    sf::Image image;
    image.create(width, height, sf::Color(255, 255, 255, 10));

    // Sphere data
    glm::vec3 center(0, 0, 10);
    glm::float32 radius = 100;

    // Ray direction
    glm::vec3 direction(0, 0, 1); //normalized value !

    // Light position
    glm::vec3 light(0, 10, 10);

    // List oh objects in our scene
    std::vector<SceneObject*> objectsList;

    SceneObject* s = new Sphere(center, radius);
    objectsList.push_back(s);

    // Compute pixel color
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; y++){
            
            // Ray origin
            glm::vec3 origin(static_cast<float>(x) - width / 2, static_cast<float>(y) - height / 2, 0);
            Ray pixel(origin, direction);

            glm::vec3 position;
            glm::vec3 normal;

            // If false, no intersection found
            if (glm::intersectRaySphere(pixel.m_origin, pixel.m_direction, center, radius, position, normal)) {

                image.setPixel(x, y, sf::Color::Green);

                //// Compute light intersection
                //glm::vec3 positionDecalee = position + 0.1f * normal;
                //glm::vec3 lightDirection = light - position;
                //glm::normalize(lightDirection);
                //glm::vec3 secondPosition;
                //glm::vec3 secondNormal;
                //if (glm::intersectRaySphere(positionDecalee, lightDirection, center, radius, secondPosition, secondNormal)) {
                //    image.setPixel(x, y, sf::Color::Green);
                //}
                //else {
                //    image.setPixel(x, y, sf::Color::Yellow);
                //}
            
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