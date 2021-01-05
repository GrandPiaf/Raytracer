#pragma once

#include <glm/glm.hpp>

#include "Ray.h"
#include <algorithm>    // std::swap

/*
	Using optimized method of https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
*/

class AABB
{
private:
	glm::vec3 bounds[2];

public:
	AABB(const glm::vec3 &minBorder, const glm::vec3 &maxBorder);
	bool intersect(const Ray &r);
};