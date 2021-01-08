#include "BVHNode.h"

#include <iostream>

BVHNode::BVHNode(std::shared_ptr<SceneObject> &sceneObject)
			: m_bbox(sceneObject->getBoundingBox()), m_sceneObject(sceneObject), m_leftChild(), m_rightChild()
			{}

BVHNode::BVHNode(AABB &bbox, std::shared_ptr<BVHNode> leftChild, std::shared_ptr<BVHNode> rightChild)
			: m_bbox(bbox), m_leftChild(leftChild), m_rightChild(rightChild)
			{}


BVHNode BVHNode::createBVHNode(std::vector<std::shared_ptr<SceneObject>> &sceneObjects) {

	std::cout << sceneObjects.size() << std::endl;

	if (sceneObjects.empty()) { // If empty, create exception, it should NOT happen 
		throw std::length_error::length_error("Cannot create a Bounding Volume Hierarchy : scene objects vector is empty");
	}

	if (sceneObjects.size() > 1) // If more than an object, create 2 liste, create children nodes with the 2 list
	{
		size_t halfPos = sceneObjects.size() / 2;
		std::vector<std::shared_ptr<SceneObject>> leftPart(sceneObjects.begin(), sceneObjects.begin() + halfPos);
		std::vector<std::shared_ptr<SceneObject>> rightPart(sceneObjects.begin() + halfPos, sceneObjects.end());

		//createBVHNode for each child
		//BVHNode::getAABB(for current node)
		//create parent node

		BVHNode leftChild = BVHNode::createBVHNode(leftPart);
		BVHNode rightChild = BVHNode::createBVHNode(rightPart);

		return BVHNode(BVHNode::getAABB(sceneObjects), std::make_shared<BVHNode>(leftChild), std::make_shared<BVHNode>(rightChild));

	}
	else {
		return BVHNode(sceneObjects[0]); // If a single element, it is a leaf, childs are null, keep the sceneObject ptr
	}

}

bool BVHNode::isLeaf() const {
	// Only need to evaluate the left child since both are linked : if one is created the other is also created.
	return m_leftChild == nullptr;
	// The same as :
	// return m_rightChild == nullptr;
	// return m_sceneObject != nullptr;
}

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