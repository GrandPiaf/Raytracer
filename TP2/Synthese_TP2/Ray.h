#pragma once

#include <glm/glm.hpp>

struct Ray
{
public:
	static unsigned long long rayCount;

	glm::vec3 m_origin;
	glm::vec3 m_direction;

	glm::vec3 invdir;
	int sign[3];

	Ray(const glm::vec3 &origin, const glm::vec3 &direction) : m_origin(origin), m_direction(glm::normalize(direction)) {
		invdir = 1.0f / m_direction; //Divion regrouped to reduce cost
		sign[0] = (invdir.x < 0);
		sign[1] = (invdir.y < 0);
		sign[2] = (invdir.z < 0);
		++rayCount;
	}
};