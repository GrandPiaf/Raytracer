#pragma once

struct PerspectiveCamera : Camera
{
	glm::vec3 m_position;
	glm::vec3 m_direction;
	float m_dist;

	PerspectiveCamera(const unsigned int &width, const unsigned int &height, const glm::vec3 &position, const glm::vec3 &direction, const float &dist) : Camera(width, height), m_position(position), m_direction(direction), m_dist(dist) {}

	Ray getRay(const unsigned int &x, const unsigned int &y) override {

		glm::vec3 origin = m_position + (-1 * m_dist * m_direction);

		glm::vec3 pixelOrigin(static_cast<float>(x) - m_width / 2, static_cast<float>(y) - m_height / 2, m_position.z);
		return Ray(origin, (pixelOrigin - origin));
	}
};