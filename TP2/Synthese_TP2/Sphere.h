#pragma once

#include <glm/gtx/intersect.hpp>

#include "SceneObject.h"

class Sphere : SceneObject
{
private:
	glm::vec3 m_center;
	glm::float32 m_radius;

public:
	Sphere(glm::vec3 center, glm::float32 radius);

	bool intersect(Ray r, glm::vec3& position, glm::vec3& normal) override;
};

Sphere::Sphere(glm::vec3 center, glm::float32 radius) : SceneObject(), m_center(center), m_radius(radius)
{
}

bool Sphere::intersect(Ray r, glm::vec3& position, glm::vec3& normal)
{
	return glm::intersectRaySphere(r.m_origin, r.m_direction, m_center, m_radius, position, normal);
}