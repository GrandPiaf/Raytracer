#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

#include "Ray.h"

class SceneObject
{
public:
	sf::Color m_color;

	SceneObject(const sf::Color &color) : m_color(color) {};
	virtual bool intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal) = 0;

};