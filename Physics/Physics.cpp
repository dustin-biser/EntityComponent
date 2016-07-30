//
// Physics.cpp
//
#include "Physics.hpp"


Physics::Physics (
	EntityID id,
	GameObject & gameObject
) 
	: Component(id, gameObject),
	  boundingBox{vec2(0.0f, 0.0f), vec2(0.0f, 0.0f)}
{

}