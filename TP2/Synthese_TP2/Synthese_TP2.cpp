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


    


    image.saveToFile("../../../result.png");
}
