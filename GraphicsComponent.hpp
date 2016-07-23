//
// GraphicsComponent.hpp
//
#pragma once

#include <vector>

// Forward declare
struct Mesh2d;
class GameObject;

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

	void draw(const GameObject & gameobject) const;

	Color color;
	const Mesh2d * mesh;
};