
#include <iostream>

#include "Synthese_TP2.h"

int main()
{

    unsigned int width = 800;
    unsigned int height = 600;

    Scene scene(width, height, Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)), sf::Color(255, 255, 255, 125));
    scene.renderImage("../../../result.png");

    sf::Texture texture;
    texture.loadFromImage(scene.getImage());  //Load Texture from image

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::RenderWindow window(sf::VideoMode(width, height), "RAYTRACER");

    while (window.isOpen()) {
    
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }//Event handling done

        window.clear();
        window.draw(sprite);
        window.display();

    }

}


template <typename T>
T changeRange(T const& OldValue, T const& OldMin, T const& OldMax, T const& NewMin, T const& NewMax) {
    T OldRange = (OldMax - OldMin);
    T NewRange = (NewMax - NewMin);
    T NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin;
    return NewValue;
}