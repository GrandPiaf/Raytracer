#include "AABB.h"

AABB::AABB(const glm::vec3 &minBorder, const glm::vec3 &maxBorder) {
	bounds[0] = minBorder;
	bounds[1] = maxBorder;
}


bool AABB::intersect(const Ray &r) {

	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	tmin = (bounds[r.sign[0]].x - r.m_origin.x) * r.invdir.x;
	tmax = (bounds[1 - r.sign[0]].x - r.m_origin.x) * r.invdir.x;
	tymin = (bounds[r.sign[1]].y - r.m_origin.y) * r.invdir.y;
	tymax = (bounds[1 - r.sign[1]].y - r.m_origin.y) * r.invdir.y;

	if ((tmin > tymax) || (tymin > tmax))
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	tzmin = (bounds[r.sign[2]].z - r.m_origin.z) * r.invdir.z;
	tzmax = (bounds[1 - r.sign[2]].z - r.m_origin.z) * r.invdir.z;

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