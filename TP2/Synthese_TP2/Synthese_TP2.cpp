
#include <iostream>
#include <sstream>
#include <chrono>

#include "Synthese_TP2.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "BVHNode.h"

std::string format_duration(std::chrono::nanoseconds duration) {

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;

    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
    duration -= microseconds;

    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

    std::stringstream ss;
    ss << hours.count() << " Hours : "
    << minutes.count() << " Minutes : "
    << seconds.count() << " Seconds : "
    << milliseconds.count() << " Milliseconds : "
    << microseconds.count() << " Microseconds : "
    << nanoseconds.count() << " Nanoseconds";
    return ss.str();
}

/* Setting static variables */
unsigned long long Ray::rayCount{ 0 };
unsigned long long AABB::intersectionCount{ 0 };
unsigned long long SceneObject::intersectionCount{ 0 };

int main(int argc, char *argv[])
{
    // To print numbers with commas
    std::locale loc = std::cout.imbue(std::locale("en_US.utf8")); //French print weird characters ....

    if (argc != 5){
        std::cerr << "Incorrect number of arguments. format : Synthese_TP2.exe <save file name> <nb generated sphere> <Structure type (0 = No structure, 1 = Only structure, 2 = Mix)> <true/false : show in SFML window>" << std::endl;
        return 1;
    }

    std::string saveFileName(argv[1]);
    unsigned int nbGenerated = atoi(argv[2]);

    unsigned int type = atoi(argv[3]);
    if (type > 2){
        std::cerr << "Incorrect structure type (0 = No structure, 1 = Only structure, 2 = Mix)" << std::endl;
        return 2;
    }

    bool showSFML;
    char* status_char = argv[4];
    std::stringstream ss;
    ss << status_char;
    ss >> std::boolalpha >> showSFML;




    unsigned int width = 1000;
    unsigned int height = 1000;
    unsigned int nbRayCastPerPixel = 8;
    unsigned int maxDepth = 3;

    // Orthogonal Camera
    //std::shared_ptr<Camera> cam = std::shared_ptr<OrthographicCamera>(new OrthographicCamera(width, height, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)) );

    // Perspective Camera
    float distanceCamera = 500;
    std::shared_ptr<Camera> cam = std::shared_ptr<PerspectiveCamera>(new PerspectiveCamera(width, height, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), distanceCamera));


    /** Creating Scene **/
    Scene scene(width, height, std::move(cam), color3(0, 0, 0));
    scene.createScene(nbGenerated, type);


    /** Time Test **/
    auto time_beforeBuildingStructure = std::chrono::high_resolution_clock::now();
    if (type != 0){
        scene.buildStructure();
    }
    auto time_beforeRender = std::chrono::high_resolution_clock::now();
    scene.renderImage(saveFileName, nbRayCastPerPixel, maxDepth);
    auto time_afterRender = std::chrono::high_resolution_clock::now();

    auto buildingStructureDuration = std::chrono::duration_cast<std::chrono::nanoseconds> (time_beforeRender - time_beforeBuildingStructure);
    std::cout << "Structure building execution time (method buildStructure) : \n" << format_duration(buildingStructureDuration) << std::endl << std::endl;

    auto renderDuration = std::chrono::duration_cast<std::chrono::nanoseconds> (time_afterRender - time_beforeRender);
    std::cout << "Raytracing execution time (method renderImage) : \n" << format_duration(renderDuration) << std::endl << std::endl;

    auto totalDuration = std::chrono::duration_cast<std::chrono::nanoseconds> (time_afterRender - time_beforeBuildingStructure);
    std::cout << "Raytracing execution time (both methods) : \n" << format_duration(totalDuration) << std::endl << std::endl;

    /** Fetching static counters **/
    std::cout << "Number of rays : " << Ray::rayCount << std::endl;
    std::cout << "Number of AABB intersection : " << AABB::intersectionCount << std::endl;
    std::cout << "Number of SceneObject intersection : " << SceneObject::intersectionCount << std::endl;
    std::cout << "Total number of intersection (AABB + SceneObject) : " << AABB::intersectionCount + SceneObject::intersectionCount << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    if (!showSFML){
        return 0;
    }

    /** Creating SFML Windows to display last rendered image**/
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

    return 0;

}