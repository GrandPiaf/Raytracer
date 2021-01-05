#include "Sphere.h"
#include <iostream>

Sphere::Sphere(const color3 &albedo, const SceneObjectType &type, const glm::vec3 &center, const float &radius) :
	SceneObject(albedo, type), m_center(center), m_radius(radius), m_radius2(radius * radius)
{}

bool Sphere::intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal, float &t)
{

	// operators + & - work on all 3 components of vec3
	glm::vec3 min = m_center - m_radius;
	glm::vec3 max = m_center + m_radius;

	//float t0x = (min.x - r.m_origin.x) / r.m_direction.x;
	//float t0y = (min.y - r.m_origin.y) / r.m_direction.y;
	//float t0z = (min.z - r.m_origin.z) / r.m_direction.z;

	//float t1x = (max.x - r.m_origin.x) / r.m_direction.x;
	//float t1y = (max.y - r.m_origin.y) / r.m_direction.y;
	//float t1z = (max.z - r.m_origin.z) / r.m_direction.z;

	float tmin = (min.x - r.m_origin.x) / r.m_direction.x; //t0x
	float tmax = (max.x - r.m_origin.x) / r.m_direction.x; //t1x

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (min.y - r.m_origin.y) / r.m_direction.y;
	float tymax = (max.y - r.m_origin.y) / r.m_direction.y;

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (min.z - r.m_origin.z) / r.m_direction.z;
	float tzmax = (max.z - r.m_origin.z) / r.m_direction.z;

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;


	if (tmin <= 0) {
		if (tmax <= 0) {
			return false;
		} else {
			t = tmax;
		}
	} else {
		t = tmin;
	}

	position = r.m_origin + t * r.m_direction * 0.9999f;
	normal = glm::normalize(position - m_center);

	return true;


	

	//float t0, t1;

	//glm::vec3 L = m_center - r.m_origin;
	//float tca = glm::dot(L, r.m_direction);

	//if (tca < 0) {
	//	return false;
	//}

	//float d2 = glm::dot(L, L) - tca * tca;

	//if (d2 > m_radius2) {
	//	return false;
	//}
	//float thc = sqrt(m_radius2 - d2);

	//t0 = tca - thc;
	//t1 = tca + thc;

	//if (t0 > t1) {
	//	std::swap(t0, t1);
	//}

	//if (t0 < 0) {
	//	t0 = t1;
	//	if (t0 < 0) {
	//		return false;
	//	}
	//}

	//t = t0;
	//
	//position = r.m_origin + t * r.m_direction;
	//normal = glm::normalize(position - m_center);
	//
	//return true;

	
	
}