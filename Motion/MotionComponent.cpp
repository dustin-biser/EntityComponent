//
// MotionComponent.cpp
//
#if false

#include "MotionComponent.hpp"
#include "GameObject.hpp"

//---------------------------------------------------------------------------------------
MotionComponent::MotionComponent()
	: velocity(0.0f, 0.0f)
{

}

//---------------------------------------------------------------------------------------
MotionComponent::~MotionComponent()
{

}

//---------------------------------------------------------------------------------------
MotionComponent * MotionComponent::clone () const
{
	return new MotionComponent(*this);
}

//---------------------------------------------------------------------------------------
void MotionComponent::update (
	GameObject * gameObject,
	float elapsedTime
) {
	vec2 pos = gameObject->transform.position;

	// Simple Euler integration step.
	pos.x += velocity.x * elapsedTime;
	pos.y += velocity.y * elapsedTime;

	gameObject->transform.position = pos;
}

#endif
