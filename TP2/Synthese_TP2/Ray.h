#pragma once

#include <glm/glm.hpp>

struct Ray
{
public:
	glm::vec3 m_origin;
	glm::vec3 m_direction;

	Ray(const glm::vec3 &origin, const glm::vec3 &direction) : m_origin(origin), m_direction(direction) {}
};