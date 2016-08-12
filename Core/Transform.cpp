//
// Transform.cpp
//
#include "Transform.hpp"

#include <cmath>

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/GameObject.hpp"

//---------------------------------------------------------------------------------------
Transform::Transform (
	const GameObject & gameObject
)
	: Component (gameObject),
	  position(0.0f, 0.0f),
	  scale(1.0f, 1.0f),
	  rotationAngle(0.0f)
{

}

//---------------------------------------------------------------------------------------
Transform::Transform()
	: position(0.0f, 0.0f),
	  scale(1.0f, 1.0f),
	  rotationAngle(0.0f)
{

}

//---------------------------------------------------------------------------------------
Transform Transform::operator * (
	const Transform & other
) const {
	Transform result;
	result.position = position + other.position;
	result.scale = scale * other.scale;
	result.rotationAngle = rotationAngle + other.rotationAngle;

	return result;
}

//---------------------------------------------------------------------------------------
vec2 Transform::operator * (const vec2 & vertex) const
{
	float x = vertex.x;
	float y = vertex.y;

	// Rotate
	const float angle = rotationAngle;
	if (std::fabs(angle) > 1.0e-6) {
		const float sinAngle = std::sin(angle);
		const float cosAngle = std::cos(angle);
		float x_new = cosAngle * x - sinAngle * y;
		float y_new = sinAngle * x + cosAngle * y;

		x = x_new;
		y = y_new;
	}

	// Scale
	x = x * scale.x;
	y = y * scale.y;


	// Translate
	x += position.x;
	y += position.y;

	return vec2{ x, y };

}

//---------------------------------------------------------------------------------------
void Transform::setParent (
	Transform & parent
) {
	m_parentId = parent.id;
	parent.addChild(*this);
}


//---------------------------------------------------------------------------------------
void Transform::addChild (
	Transform & child
) {
	const EntityID childId = child.id;

	// Check that child is not already in child list.
	for (const auto & entityId : m_childList) {
		if (entityId == childId) {
			return;
		}
	}
	m_childList.push_back(childId);
}


//---------------------------------------------------------------------------------------
Transform * Transform::getParent() const
{
	if (m_parentId != EntityID::NO_ENTITY) {
		return ComponentPoolLocator<Transform>::getPool()->getComponent(m_parentId);
	}
	else {
		return nullptr;
	}
}

//---------------------------------------------------------------------------------------
Transform * Transform::childAtIndex (
	size_t index
) const {
	if (m_childList.size() > index) {
		ComponentPool<Transform> * transformPool = 
			ComponentPoolLocator<Transform>::getPool();
		return transformPool->getComponent(m_childList[index]);
	}
	else {
		return nullptr;
	}
}

//---------------------------------------------------------------------------------------
Transform & Transform::operator = (
	const Transform & other
) {
	this->position = other.position;
	this->scale = other.scale;
	this->rotationAngle = other.rotationAngle;

	this->m_parentId.clear();

	// Replicate other's child Transforms.
	ComponentPool<Transform> * componentPool = ComponentPoolLocator<Transform>::getPool();
	for (auto otherChildID : other.m_childList) {
		Transform * otherChildTransform = componentPool->getComponent(otherChildID);

		// Create a new GameOjbect with Transform that is a copy of other.
		GameObject * gameObject = new GameObject(otherChildTransform->gameObject());

		Transform & childTransform = gameObject->transform();
		childTransform.m_parentId = this->id;

		this->m_childList.push_back(childTransform.id);
	}

	return *this;
}