//
// MotionComponent.cpp
//
#include "MotionComponent.hpp"

//---------------------------------------------------------------------------------------
MotionComponent::~MotionComponent()
{

}

//---------------------------------------------------------------------------------------
MotionComponent * MotionComponent::clone () const
{
	return new MotionComponent(*this);
}
