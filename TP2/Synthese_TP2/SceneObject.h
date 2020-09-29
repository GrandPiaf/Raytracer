#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

#include "Ray.h"

typedef glm::vec3 color3;

class SceneObject
{
public:
	color3 m_color;

	SceneObject(const color3 &color) : m_color(color) {};
	virtual bool intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal, float &t) = 0;

};