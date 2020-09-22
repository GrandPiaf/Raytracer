#pragma once

class SceneObject
{
public:
	virtual bool intersect(Ray r, glm::vec3& position, glm::vec3& normal) = 0;

};