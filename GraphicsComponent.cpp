//
// GraphicsComponent.cpp
//
#include "GraphicsComponent.hpp"

//---------------------------------------------------------------------------------------
GraphicsComponent::GraphicsComponent()
	: color{ 0.0f, 0.0f, 0.0f },
	   mesh(nullptr)
{

}

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
GraphicsComponent * GraphicsComponent::clone() const
{
	return new GraphicsComponent(*this);
}

//---------------------------------------------------------------------------------------
GraphicsComponent::~GraphicsComponent()
{

}
