#pragma once

#include <glm/glm.hpp>

struct Camera
{
	glm::vec3 m_position;
	glm::vec3 m_direction;

	Camera(const glm::vec3 &position, const glm::vec3 &direction) : m_position(position), m_direction(direction) {}
};