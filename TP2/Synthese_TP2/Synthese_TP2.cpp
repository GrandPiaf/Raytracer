// Synthese_TP2.cpp : définit le point d'entrée de l'application.
//

#include "Synthese_TP2.h"
#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"

using namespace std;

int main()
{

    /** CODE EXAMPLE SFML **/



    sf::RenderWindow window(sf::VideoMode(800, 800), "Main Window");
    sf::CircleShape shape(300.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
