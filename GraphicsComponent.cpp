#include "GraphicsComponent.hpp"

//---------------------------------------------------------------------------------------
GraphicsComponent::GraphicsComponent (
	const Color & color,
	const Mesh2d * mesh
)
	: color(color),
	  mesh(mesh)
{

}

//---------------------------------------------------------------------------------------
GraphicsComponent::GraphicsComponent()
	: color{ 0.0f, 0.0f, 0.0f }
{

}


//---------------------------------------------------------------------------------------
void GraphicsComponent::draw (
	const GameObject & gameobject
) const {

	
}

