#pragma once

#include <algorithm>    // std::swap
#include <vector>

#include <glm/glm.hpp>

#include "Ray.h"

/*
	Using optimized method of https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
*/

class AABB
{
private:
	glm::vec3 m_bounds[2];
	glm::vec3 m_centroid;

public:
	static unsigned long long intersectionCount;

	AABB(const glm::vec3 &minBorder, const glm::vec3 &maxBorder);
	bool intersect(const Ray &r) const;

	const glm::vec3 & maximum() const;
	const glm::vec3 & minimum() const;
	const glm::vec3 & centroid() const;
};