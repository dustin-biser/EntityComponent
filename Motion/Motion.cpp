//
// MotionComponent.cpp
//
#include "Motion.hpp"

//---------------------------------------------------------------------------------------
Motion::Motion (
	EntityID id,
	GameObject & gameObject
)
	: Component(id, gameObject),
	  velocity(vec2(0.0f, 0.0f))
{

}