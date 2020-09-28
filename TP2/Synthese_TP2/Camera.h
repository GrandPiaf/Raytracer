#pragma once

#include <glm/glm.hpp>

struct Camera
{
	unsigned int m_width;
	unsigned int m_height;

	Camera(const unsigned int &width, const unsigned int &height) : m_width(width), m_height(height) {}

	virtual Ray getRay(const unsigned int &x, const unsigned int &y) = 0;
};