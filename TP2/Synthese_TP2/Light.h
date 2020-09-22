#pragma once

#include <glm/glm.hpp>

struct Light
{
public:
	glm::vec3 m_position;
	glm::vec3 m_color;

	Light(glm::vec3 position, glm::vec3 color) : m_position(position), m_color(color) {}

	Ray getRayFrom(glm::vec3& position) {
		return Ray(position, (m_position - position) );
	}
};