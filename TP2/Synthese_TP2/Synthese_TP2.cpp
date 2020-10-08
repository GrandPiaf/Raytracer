
#include <iostream>
#include <sstream>
#include <chrono>

#include "Synthese_TP2.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"


std::string format_duration(std::chrono::milliseconds ms) {
    using namespace std::chrono;
    auto secs = duration_cast<seconds>(ms);
    ms -= duration_cast<milliseconds>(secs);
    auto mins = duration_cast<minutes>(secs);
    secs -= duration_cast<seconds>(mins);
    auto hour = duration_cast<hours>(mins);
    mins -= duration_cast<minutes>(hour);

    std::stringstream ss;
    ss << hour.count() << " Hours : " << mins.count() << " Minutes : " << secs.count() << " Seconds : " << ms.count() << " Milliseconds";
    return ss.str();
}


int main()
{

    unsigned int width = 1000;
    unsigned int height = 1000;

    // Orthogonal Camera
    //std::shared_ptr<Camera> cam = std::shared_ptr<OrthographicCamera>(new OrthographicCamera(width, height, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)) );

    // Perspective Camera
    float distanceCamera = 500;
    std::shared_ptr<Camera> cam = std::shared_ptr<PerspectiveCamera>(new PerspectiveCamera(width, height, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), distanceCamera));

    Scene scene(width, height, std::move(cam), color3(0, 0, 0));


    auto t1 = std::chrono::high_resolution_clock::now();
    scene.renderImage("../../../result.png");
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (t2 - t1);
    std::cout << "Raytracing execution time (method renderImage) : " << format_duration(duration) << std::endl;


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