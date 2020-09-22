#pragma once

#include <glm/gtx/intersect.hpp>

#include "SceneObject.h"

class Sphere : public SceneObject
{
private:
	glm::vec3 m_center;
	float m_radius;
	float m_radius2;

public:
	Sphere(const sf::Color &color, const glm::vec3 &center, const float &radius);

	bool intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal) override;
};
