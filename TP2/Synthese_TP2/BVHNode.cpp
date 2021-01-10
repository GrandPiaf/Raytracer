#include "BVHNode.h"

#include <iostream>

BVHNode::BVHNode(std::shared_ptr<SceneObject> &sceneObject)
			: m_bbox(sceneObject->getBoundingBox()), m_sceneObject(sceneObject), m_leftChild(), m_rightChild() {}

BVHNode::BVHNode(AABB &bbox, std::shared_ptr<BVHNode> leftChild, std::shared_ptr<BVHNode> rightChild)
			: m_bbox(bbox), m_leftChild(leftChild), m_rightChild(rightChild) {}


enum SortingAxis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};
struct CompareSceneObjects {

	explicit CompareSceneObjects(SortingAxis axis) : m_axis(axis) {}

	bool operator()(const std::shared_ptr<SceneObject> &so1, const std::shared_ptr<SceneObject> &so2) {
		

		const glm::vec3 &so1BBoxMin = so1->getBoundingBox().minimum();
		const glm::vec3 &so2BBoxMin = so2->getBoundingBox().minimum();

		switch (m_axis)
		{
			case X_AXIS:
				if (so1BBoxMin.x == so2BBoxMin.x) {
					if (so1BBoxMin.y == so2BBoxMin.y) {
						return so1BBoxMin.z < so2BBoxMin.z;
					}
					return so1BBoxMin.y < so2BBoxMin.y;
				}
				return so1BBoxMin.x < so2BBoxMin.x;
				break;

			case Y_AXIS:
				if (so1BBoxMin.y == so2BBoxMin.y) {
					if (so1BBoxMin.z == so2BBoxMin.z) {
						return so1BBoxMin.x < so2BBoxMin.x;
					}
					return so1BBoxMin.z < so2BBoxMin.z;
				}
				return so1BBoxMin.y < so2BBoxMin.y;
				break;

			case Z_AXIS:
				if (so1BBoxMin.z == so2BBoxMin.z) {
					if (so1BBoxMin.x == so2BBoxMin.x) {
						return so1BBoxMin.y < so2BBoxMin.y;
					}
					return so1BBoxMin.x < so2BBoxMin.x;
				}
				return so1BBoxMin.z < so2BBoxMin.z;
				break;
		}
	}

	SortingAxis m_axis;
};

BVHNode BVHNode::createBVHNode(std::vector<std::shared_ptr<SceneObject>> &sceneObjects) {

	if (sceneObjects.empty()) { // If empty, create exception, it should NOT happen 
		throw std::length_error::length_error("Cannot create a Bounding Volume Hierarchy : scene objects vector is empty");
	}

	if (sceneObjects.size() > 1) // If more than an object, create 2 liste, create children nodes with the 2 list
	{
		//retrieve the current bounding box
		AABB currentBBox = BVHNode::getAABB(sceneObjects);

		//Compute the bounding box size on each axis
		float sizeX = currentBBox.maximum().x - currentBBox.minimum().x;
		float sizeY = currentBBox.maximum().y - currentBBox.minimum().y;
		float sizeZ = currentBBox.maximum().z - currentBBox.minimum().z;

		//Get the max size of one of the axis
		float sizeMAX = std::max(sizeX, std::max(sizeY, sizeZ));

		//Create the chosen axis variable
		SortingAxis chosenAxis;

		//Find which axis is the longest & set the chosenAxis variable to the longest
		if (sizeX == sizeMAX) {
			chosenAxis = SortingAxis::X_AXIS;
		} else if (sizeY == sizeMAX) {
			chosenAxis = SortingAxis::Y_AXIS;
		} else { // if it is neither X or y axis, we choose the z axis
			chosenAxis = SortingAxis::Z_AXIS;
		}

		//Sort from the axis
		std::sort(sceneObjects.begin(), sceneObjects.end(), CompareSceneObjects(chosenAxis));

		//Split vector
		size_t halfPos = sceneObjects.size() / 2;
		std::vector<std::shared_ptr<SceneObject>> leftPart(sceneObjects.begin(), sceneObjects.begin() + halfPos);
		std::vector<std::shared_ptr<SceneObject>> rightPart(sceneObjects.begin() + halfPos, sceneObjects.end());

		//Create childs from sub-vector
		BVHNode leftChild = BVHNode::createBVHNode(leftPart);
		BVHNode rightChild = BVHNode::createBVHNode(rightPart);

		//Create the current node
		return BVHNode(currentBBox, std::make_shared<BVHNode>(leftChild), std::make_shared<BVHNode>(rightChild));

	}
	else {
		//Create the current (leaf) node
		return BVHNode(sceneObjects[0]); // If a single element, it is a leaf, childs are null, keep the sceneObject ptr
	}

}

std::optional<std::shared_ptr<SceneObject>> BVHNode::findClosestIntersection(const Ray &ray, glm::vec3 &position, glm::vec3 &normal, float &t) {

	//Small optimization : if this BBox found an intersection that is FURTHER than the last previous one found, we directly return nullopt, we don't have to go further in the tree
	//That means : we need an argument for the previous t value found in the search

	//If the current BBox is NOT intersected by the ray, we return nullopt
	if (!m_bbox.intersect(ray)) {
		return std::nullopt;
	}

	//If the current node is a leaf
	if (isLeaf()) {
		//We try to intersect the stored scene object
		if (m_sceneObject->intersect(ray, position, normal, t)) {
			//If we do intersect the scene object, we return it's position, normal and t value (already computed in above intersect method)
			return { m_sceneObject };
		}

		//If we do not intersect the stored scene object, we return nullopt
		return std::nullopt;
	}

	//Else : not a leaf

	//Compute each child closest intersection
	float leftChild_t;
	glm::vec3 leftChild_position;
	glm::vec3 leftChild_normal;
	std::optional<std::shared_ptr<SceneObject>> leftChildIntersectedObject = m_leftChild->findClosestIntersection(ray, leftChild_position, leftChild_normal, leftChild_t);

	float rightChild_t;
	glm::vec3 rightChild_position;
	glm::vec3 rightChild_normal;
	std::optional<std::shared_ptr<SceneObject>> rightChildIntersectedObject = m_rightChild->findClosestIntersection(ray, rightChild_position, rightChild_normal, rightChild_t);

	//4 cases : nothing found, one of them is found, two of them found

	//If nothing found, returning nullopt
	if (!rightChildIntersectedObject && !leftChildIntersectedObject) {
		return std::nullopt;
	}

	//Only left child has an intersection, return left intersection
	if (!rightChildIntersectedObject) { 
		position = leftChild_position;
		normal = leftChild_normal;
		t = leftChild_t;
		return leftChildIntersectedObject;
	}

	//Only right child has an intersection, return right intersection
	if (!leftChildIntersectedObject) {
		position = rightChild_position;
		normal = rightChild_normal;
		t = rightChild_t;
		return rightChildIntersectedObject;
	}

	//Each child found something, return closest intersection (depending on theit t values)
	
	//Right child is closest
	if (rightChild_t < leftChild_t) {
		position = rightChild_position;
		normal = rightChild_normal;
		t = rightChild_t;
		return rightChildIntersectedObject;
	}

	//Left child is closest
	position = leftChild_position;
	normal = leftChild_normal;
	t = leftChild_t;
	return leftChildIntersectedObject;

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