//
// GraphicsComponent.hpp
//
#pragma once

#include "EntityID.hpp"
#include <vector>

// Forward declare
struct Mesh2d;

struct Color {
	float red;
	float green;
	float blue;
};

// Abstract class
class GraphicsComponent {
public:
	GraphicsComponent();

	GraphicsComponent (
		const Color & color,
		const Mesh2d * mesh
	);

	EntityID id;
	Color color;
	const Mesh2d * mesh;
};