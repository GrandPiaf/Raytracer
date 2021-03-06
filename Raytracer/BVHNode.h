#pragma once

//As Bounding Volume Hierarchy

#include <memory>
#include <optional>

#include "AABB.h"
#include "SceneObject.h"

class BVHNode {

private:
	BVHNode(std::shared_ptr<SceneObject> &sceneObject);
	BVHNode(AABB &bbox, std::shared_ptr<BVHNode> leftChild, std::shared_ptr<BVHNode> rightChild);

public:
	const AABB m_bbox;
	const std::shared_ptr<SceneObject> m_sceneObject;
	std::shared_ptr<BVHNode> m_leftChild;
	std::shared_ptr<BVHNode> m_rightChild;

public:
	bool isLeaf() const;
	std::optional<std::shared_ptr<SceneObject>> findClosestIntersection(const Ray &ray, glm::vec3 &position, glm::vec3 &normal, float &t);

	static BVHNode createBVHNode(std::vector<std::shared_ptr<SceneObject>> &sceneObjects); // Factory Method
	static AABB getAABB(std::vector<std::shared_ptr<SceneObject>> &sceneObjects); // Factory Method
};