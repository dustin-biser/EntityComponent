//
// Material.cpp
//
#include "Rendering.hpp"

//---------------------------------------------------------------------------------------
Rendering::Rendering (
	EntityID id,
	GameObject & gameObject
)
	: Component (id, gameObject),
	  color {0.0f, 0.0f, 0.0f},
	  mesh (nullptr)
{

}

//---------------------------------------------------------------------------------------
Rendering * Rendering::clone() const
{
	return new Rendering(*this);
}

//---------------------------------------------------------------------------------------
Rendering::~Rendering()
{

}
