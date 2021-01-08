#pragma once

//As Bounding Volume Hierarchy

#include <memory>

#include "AABB.h"
#include "SceneObject.h"

class BVHNode {

public:
	AABB m_bbox;
	std::unique_ptr<BVHNode> m_leftChild;
	std::unique_ptr<BVHNode> m_rightChild;

public:
	BVHNode(std::vector<std::shared_ptr<SceneObject>> &sceneObjects);

	static AABB getAABB(std::vector<std::shared_ptr<SceneObject>> &sceneObjects);
};