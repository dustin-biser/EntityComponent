//
// Material.cpp
//
#include "Rendering.hpp"

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"

//---------------------------------------------------------------------------------------
Rendering::Rendering()
	: color {0.0f, 0.0f, 0.0f},
	  mesh(&defaultMesh)
{

}

//---------------------------------------------------------------------------------------
Rendering::Rendering (
	const GameObject & gameObject
)
	: Component (gameObject),
	  color {0.0f, 0.0f, 0.0f},
	  mesh (&defaultMesh)
{

}

//---------------------------------------------------------------------------------------
Rendering & Rendering::operator = (
	const Rendering & other
) {
	this->color = other.color;
	this->mesh = other.mesh;

	return *this;
}

