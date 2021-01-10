
#include <iostream>
#include <sstream>
#include <chrono>

#include "Synthese_TP2.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "BVHNode.h"


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

    /** BVHNode tests **/
    std::shared_ptr<SceneObject> sphereA(new Sphere(color3(0, 1, 1), SceneObjectType::REFLECTIVE, glm::vec3(0, 0, 200), 100));
    std::shared_ptr<SceneObject> sphereB(new Sphere(color3(1, 1, 0), SceneObjectType::REFLECTIVE, glm::vec3(100, 200, 400), 150));
    std::shared_ptr<SceneObject> sphereC(new Sphere(color3(1, 0, 1), SceneObjectType::REFLECTIVE, glm::vec3(-300, -300, 800), 200));

    std::vector<std::shared_ptr<SceneObject>> m_objectList;
    m_objectList.emplace_back(sphereA);
    m_objectList.emplace_back(sphereC);
    m_objectList.emplace_back(sphereB);

    std::cout << "BEFORE" << std::endl;
    for (auto &object : m_objectList) {
        std::cout << "Sphere min bbox : " << object->getBoundingBox().minimum().x << " / " << object->getBoundingBox().minimum().y << " / " << object->getBoundingBox().minimum().z << std::endl;
    }
    std::cout << std::endl;

    BVHNode root = BVHNode::createBVHNode(m_objectList);

    std::cout << "AFTER" << std::endl;
    for (auto &object : m_objectList) {
        std::cout << "Sphere min bbox : " << object->getBoundingBox().minimum().x << " / " << object->getBoundingBox().minimum().y << " / " << object->getBoundingBox().minimum().z << std::endl;
    }

    return 0;





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


    ///** Bounce Test **/
    //scene.buildStructure();
    //for (unsigned int i = 0; i <= maxDepth; i++) {
    //    std::stringstream ss;
    //    ss << "../../../../BounceResults/result_C" << i << ".png";
    //    scene.renderImage(ss.str(), nbRayCastPerPixel, i);
    //}


    /** Time Test **/
    auto time_beforeBuildingStructure = std::chrono::high_resolution_clock::now();
    scene.buildStructure();
    auto time_beforeRender = std::chrono::high_resolution_clock::now();
    scene.renderImage("../../../result.png", nbRayCastPerPixel, maxDepth);
    auto time_afterRender = std::chrono::high_resolution_clock::now();

    auto buildingStructureDuration = std::chrono::duration_cast<std::chrono::milliseconds> (time_beforeRender - time_beforeBuildingStructure);
    std::cout << "Structure building execution time (method buildStructure) : " << format_duration(buildingStructureDuration) << std::endl << std::endl;

    auto renderDuration = std::chrono::duration_cast<std::chrono::milliseconds> (time_afterRender - time_beforeRender);
    std::cout << "Raytracing execution time (method renderImage) : " << format_duration(renderDuration) << std::endl << std::endl;

    auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds> (time_afterRender - time_beforeBuildingStructure);
    std::cout << "Raytracing execution time (both methods) : " << format_duration(totalDuration) << std::endl << std::endl;


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

}