#pragma once

#include <string>
#include <functional>
#include <optional>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/constants.hpp>

#include <SFML/Graphics.hpp>

#include "Ray.h"
#include "Light.h"
#include "Camera.h"

#include "SceneObject.h"
#include "Sphere.h"

class Scene
{

private:
	unsigned int m_width;
	unsigned int m_height;
	std::shared_ptr<Camera> m_camera;
	std::vector<Light> m_lightList;
	std::vector<std::shared_ptr<SceneObject>> m_objectList;
	sf::Color m_backgroundColor;
	sf::Image m_image;

public:
	Scene(unsigned int width, unsigned int height, std::shared_ptr<Camera> camera, const sf::Color &backgroundColor);
	~Scene();

	void renderImage(const std::string &fileName);

	const sf::Image &getImage() const;

private:
	sf::Color Scene::rayTracePixel(const Ray &ray);
	std::optional<std::shared_ptr<SceneObject>> findClosestIntersection(const Ray &ray, glm::vec3 &position, glm::vec3 &normal);

};