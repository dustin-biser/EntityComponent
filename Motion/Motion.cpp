//
// MotionComponent.cpp
//
#include "Motion.hpp"


//---------------------------------------------------------------------------------------
Motion::Motion()
	: velocity(vec2(0.0f, 0.0f))
{

}

//---------------------------------------------------------------------------------------
Motion::Motion (
	const GameObject & gameObject
)
	: Component(gameObject),
	  velocity(vec2(0.0f, 0.0f))
{

}

//---------------------------------------------------------------------------------------
Motion & Motion::operator = (
	const Motion & other
) {
	this->velocity = other.velocity;

	return *this;
}

