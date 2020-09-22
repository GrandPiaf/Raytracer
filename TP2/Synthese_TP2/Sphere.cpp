#include "Sphere.h"

Sphere::Sphere(const sf::Color &color, const glm::vec3 &center, const glm::float32 &radius) : SceneObject(color), m_center(center), m_radius(radius)
{
}

bool Sphere::intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal)
{
	return glm::intersectRaySphere(r.m_origin, r.m_direction, m_center, m_radius, position, normal);
}