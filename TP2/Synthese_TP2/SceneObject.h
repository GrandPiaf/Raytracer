#pragma once

#include <glm/glm.hpp>
#include "Ray.h"

class SceneObject
{
public:
	virtual bool intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal) = 0;

};