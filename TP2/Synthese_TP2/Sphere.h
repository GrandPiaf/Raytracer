#pragma once

#include <glm/gtx/intersect.hpp>

#include "SceneObject.h"

class Sphere : public SceneObject
{
private:
	glm::vec3 m_center;
	glm::float32 m_radius;

public:
	Sphere(const glm::vec3 &center, const glm::float32 &radius);

	bool intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal) override;
};
