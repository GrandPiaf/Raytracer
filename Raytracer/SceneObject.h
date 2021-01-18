#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

#include "Ray.h"
#include "SceneObjectType.h"
#include "AABB.h"

typedef glm::vec3 color3;

class SceneObject
{
public:
	static unsigned long long intersectionCount;

	color3 m_albedo;
	SceneObjectType m_type;

	SceneObject(const color3 &albedo, const SceneObjectType &type) : m_albedo(albedo), m_type(type) {};
	virtual bool intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal, float &t){
		++intersectionCount;
		return true;
	};
	virtual const AABB& getBoundingBox() = 0; //Could be a ptr
};