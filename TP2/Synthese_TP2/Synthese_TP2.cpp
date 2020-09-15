// Synthese_TP2.cpp : définit le point d'entrée de l'application.
//

#include "Synthese_TP2.h"
#include "glm/glm.hpp"

#include "SFML/Graphics.hpp"

using namespace std;

int main()
{

    unsigned int width = 800;
    unsigned int height = 600;

    // Create image and fill it with calculated pixels
    sf::Image image;
    image.create(width, height);


    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; y++){
            image.setPixel(x, y, sf::Color(
                changeRange(x*width, (unsigned int)0, width * height, (unsigned int)0, (unsigned int)255),
                changeRange(y*width, (unsigned int)0, width * height, (unsigned int)0, (unsigned int)255),
                changeRange((unsigned int)0, (unsigned int)0, width * height, (unsigned int)0, (unsigned int)255)
            ));
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