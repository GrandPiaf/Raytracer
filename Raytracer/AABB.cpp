#include "AABB.h"

AABB::AABB(const glm::vec3 &minBorder, const glm::vec3 &maxBorder) {
	m_bounds[0] = minBorder;
	m_bounds[1] = maxBorder;
	m_centroid = (maxBorder + minBorder) / 2.0f;
}

const glm::vec3 & AABB::maximum() const {
	return m_bounds[1];
}

const glm::vec3 & AABB::minimum() const {
	return m_bounds[0];
}

const glm::vec3 &AABB::centroid() const {
	return m_centroid;
}

bool AABB::intersect(const Ray &r) const {
	++intersectionCount;

	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	tmin = (m_bounds[r.sign[0]].x - r.m_origin.x) * r.invdir.x;
	tmax = (m_bounds[1 - r.sign[0]].x - r.m_origin.x) * r.invdir.x;
	tymin = (m_bounds[r.sign[1]].y - r.m_origin.y) * r.invdir.y;
	tymax = (m_bounds[1 - r.sign[1]].y - r.m_origin.y) * r.invdir.y;

	if ((tmin > tymax) || (tymin > tmax))
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	tzmin = (m_bounds[r.sign[2]].z - r.m_origin.z) * r.invdir.z;
	tzmax = (m_bounds[1 - r.sign[2]].z - r.m_origin.z) * r.invdir.z;

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;

	if (tmin <= 0 && tmax <= 0) {
		return false;
	}

	return true;

}