#pragma once

#include <glm/gtx/intersect.hpp>
#include <glm/gtx/norm.hpp>

#include "SceneObject.h"

class Sphere : public SceneObject
{
private:
	const glm::vec3 m_center;
	const float m_radius;
	const float m_radius2;
	AABB m_bbox;

public:
	Sphere(const color3 &albedo, const SceneObjectType &type, const glm::vec3 &center, const float &radius);
	bool intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal, float &t) override;
	const AABB &getBoundingBox() override;

};
