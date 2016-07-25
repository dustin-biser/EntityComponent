//
// PhysicsComponent.cpp
//
#include "PhysicsComponent.hpp"

//---------------------------------------------------------------------------------------
PhysicsComponent::PhysicsComponent()
{

}

//---------------------------------------------------------------------------------------
PhysicsComponent::~PhysicsComponent()
{

}

//---------------------------------------------------------------------------------------
PhysicsComponent * PhysicsComponent::clone() const
{
	return new PhysicsComponent(*this);
}
