
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

    /*
    std::vector<int> master{ 1, 2, 3 };

    size_t halfPos = master.size() / 2;
    std::vector<int> fP(master.begin(), master.begin() + halfPos);
    std::vector<int> lP(master.begin() + halfPos, master.end());

    print("Master : ", master);
    print("FirstPart : ", fP);
    print("LastPart : ", lP);

    return 0;
    */


    /*
    std::unique_ptr<int> ptr;

    if (ptr){
        std::cout << "before reset, ptr is: " << *ptr << '\n';
    }
    else {
        std::cout << "before reset, ptr is empty" << std::endl;
    }
    -
    ptr.reset(new int(42)); //Empty is nullptr

    if (ptr) {
        std::cout << "after reset, ptr is: " << *ptr << '\n';
    }
    else {
        std::cout << "after reset, ptr is empty" << std::endl;
    }

    return 0;
    */


    /*
    glm::vec3 a(0, -5, 0);
    glm::vec3 b(-10, 0, 5);

    glm::vec3 test = glm::min(a, b);
    
    std::cout << test.x << " / " << test.y << " / " << test.z << std::endl;

    return 0;
    */


    /** BVHNode tests **/
    std::shared_ptr<SceneObject> sphereA(new Sphere(color3(0, 1, 1), SceneObjectType::REFLECTIVE, glm::vec3(0, 0, 200), 100));
    std::shared_ptr<SceneObject> sphereB(new Sphere(color3(1, 1, 0), SceneObjectType::REFLECTIVE, glm::vec3(100, 200, 400), 150));
    std::shared_ptr<SceneObject> sphereC(new Sphere(color3(1, 0, 1), SceneObjectType::REFLECTIVE, glm::vec3(-300, -300, 800), 200));

    std::vector<std::shared_ptr<SceneObject>> m_objectList;
    m_objectList.emplace_back(sphereA);
    m_objectList.emplace_back(sphereB);
    m_objectList.emplace_back(sphereC);

    std::cout << "Sphere A min bbox : " << sphereA->getBoundingBox().minimum().x << " / " << sphereA->getBoundingBox().minimum().y << " / " << sphereA->getBoundingBox().minimum().z << std::endl;
    std::cout << "Sphere A max bbox : " << sphereA->getBoundingBox().maximum().x << " / " << sphereA->getBoundingBox().maximum().y << " / " << sphereA->getBoundingBox().maximum().z << std::endl;

    std::cout << "Sphere B min bbox : " << sphereB->getBoundingBox().minimum().x << " / " << sphereB->getBoundingBox().minimum().y << " / " << sphereB->getBoundingBox().minimum().z << std::endl;
    std::cout << "Sphere B max bbox : " << sphereB->getBoundingBox().maximum().x << " / " << sphereB->getBoundingBox().maximum().y << " / " << sphereB->getBoundingBox().maximum().z << std::endl;

    std::cout << "Sphere C min bbox : " << sphereC->getBoundingBox().minimum().x << " / " << sphereC->getBoundingBox().minimum().y << " / " << sphereC->getBoundingBox().minimum().z << std::endl;
    std::cout << "Sphere C max bbox : " << sphereC->getBoundingBox().maximum().x << " / " << sphereC->getBoundingBox().maximum().y << " / " << sphereC->getBoundingBox().maximum().z << std::endl;

    BVHNode root(m_objectList);

    std::cout << "Root min bbox : " << root.m_bbox.minimum().x << " / " << root.m_bbox.minimum().y << " / " << root.m_bbox.minimum().z << std::endl;
    std::cout << "Root max bbox : " << root.m_bbox.maximum().x << " / " << root.m_bbox.maximum().y << " / " << root.m_bbox.maximum().z << std::endl;


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