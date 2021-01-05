#pragma once

#include <glm/glm.hpp>

class AABB
{
private:
	glm::vec3 m_minBorder;
	glm::vec3 m_maxBorder;

public:
	AABB(const glm::vec3 &minBorder, const glm::vec3 &maxBorder);

};