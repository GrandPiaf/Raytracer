#include "BVHNode.h"

BVHNode::BVHNode(std::vector<std::shared_ptr<SceneObject>> &sceneObjects) : m_bbox(BVHNode::getAABB(sceneObjects)), m_leftChild(), m_rightChild() {};

// static
AABB BVHNode::getAABB(std::vector<std::shared_ptr<SceneObject>> &sceneObjects) {
	
	constexpr float floatMax = std::numeric_limits<float>::max(); //Maximum positive value
	constexpr float floatMin = -std::numeric_limits<float>::max(); //Minimum negative value

	glm::vec3 min(floatMax, floatMax, floatMax), max(floatMin, floatMin, floatMin);

	for (auto &object : sceneObjects) {

		const AABB &objectBBox = object->getBoundingBox();
		min = glm::min(min, objectBBox.minimum());
		max = glm::max(max, objectBBox.maximum());

	}

	return AABB(min, max);

}