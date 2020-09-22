#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
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
	Camera m_camera;
	std::vector<Light> m_lightList;
	std::vector<std::unique_ptr<SceneObject>> m_objectList;
	sf::Color m_backgroundColor;
	sf::Image m_image;

public:
	Scene(unsigned int width, unsigned int height, const Camera &camera, const sf::Color &backgroundColor);
	~Scene();

	void renderImage(const std::string &fileName);

	const sf::Image getImage();

private:
	sf::Color Scene::rayTracePixel(unsigned int x, unsigned int y);

};