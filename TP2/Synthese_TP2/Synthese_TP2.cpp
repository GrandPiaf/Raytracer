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

    sf::RenderWindow window(sf::VideoMode(width, height), "Raytracer");

    // Create image and fill it with calculated pixels
    sf::Image image;
    image.create(width, height, sf::Color::Magenta); // Black

    // Create Sprite from Texture from Image
    sf::Texture texture;
    texture.loadFromImage(image);

    // Sprite is the rendered image
    sf::Sprite sprite;
    sprite.setTexture(texture);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}
