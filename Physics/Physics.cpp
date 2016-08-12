//
// Physics.cpp
//
#include "Physics.hpp"


//---------------------------------------------------------------------------------------
Physics::Physics()
	: boundingBox {vec2(0.0f, 0.0f), vec2(0.0f, 0.0f)}
{

}

//---------------------------------------------------------------------------------------
Physics::Physics (
	const GameObject & gameObject
)
	: Component(gameObject),
	  boundingBox {vec2(0.0f, 0.0f), vec2(0.0f, 0.0f)}
{

}

//---------------------------------------------------------------------------------------
Physics & Physics::operator = (
	const Physics & other
) {
	this->boundingBox = other.boundingBox;

	return *this;
}
