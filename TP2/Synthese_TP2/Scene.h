#pragma once

// STD
#include <string>
#include <functional>
#include <optional>
#include <random>

#include <iostream>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/constants.hpp>

// SFML
#include <SFML/Graphics.hpp>

// Project
#include "Ray.h"
#include "Light.h"
#include "Camera.h"

#include "SceneObject.h"
#include "Sphere.h"

typedef glm::vec3 color3;

class Scene
{

private:
	unsigned int m_width;
	unsigned int m_height;
	std::shared_ptr<Camera> m_camera;
	std::vector<Light> m_lightList;
	std::vector<std::shared_ptr<SceneObject>> m_objectList;
	color3 m_backgroundColor;
	sf::Image m_image;

	std::mt19937 m_gen; //(757617000);
	std::uniform_real_distribution<float> m_disPosition; //(0.0f, 1000.0f);
	std::uniform_real_distribution<float> m_disSize; //(1.0f, 50.0f);
	std::uniform_real_distribution<float> m_disOffsetRay; //(-1.0f, 1.0f);

public:
	Scene(unsigned int width, unsigned int height, std::shared_ptr<Camera> camera, const color3 &backgroundColor);
	~Scene();

	void renderImage(const std::string &fileName);

	const sf::Image &getImage() const;

	static color3 CalculateIntensity(const glm::vec3 &position, const glm::vec3 &normal, const Light &light, const Ray &toLightRay, const color3 &albedo);

private:
	void createScene();
	void generateSphere(unsigned int nb);

	color3 rayTracePixel(const Ray &ray);
	std::optional<std::shared_ptr<SceneObject>> findClosestIntersection(const Ray &ray, glm::vec3 &position, glm::vec3 &normal);

	bool lightIntersection(const glm::vec3 &position, const Light &light, glm::vec3 &positionLightIntersected, glm::vec3 &normalLightIntersected);

	color3 computeDiffuseObject(const glm::vec3 &position, const glm::vec3 &normal, const std::shared_ptr<SceneObject> &object);
	color3 computeReflectiveObject(const glm::vec3 &position, const glm::vec3 &normal, const Ray &ray);

	void createImage(std::string path, std::vector<std::vector<color3>> pixels);
	sf::Color convertPixel(color3 &p);

};


//template <typename T>
//T changeRange(T const &OldValue, T const &OldMin, T const &OldMax, T const &NewMin, T const &NewMax);