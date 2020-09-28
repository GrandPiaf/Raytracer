#pragma once

struct OrthographicCamera : Camera
{
	glm::vec3 m_position;
	glm::vec3 m_direction;

	OrthographicCamera(const unsigned int &width, const unsigned int &height, const glm::vec3 &position, const glm::vec3 &direction) : Camera(width, height), m_position(position), m_direction(direction) {}

	Ray getRay(const unsigned int &x, const unsigned int &y) override {
		glm::vec3 origin(static_cast<float>(x) - m_width / 2, static_cast<float>(y) - m_height / 2, 0);
		return Ray(origin, m_direction);
	}
};