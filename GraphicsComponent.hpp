//
// GraphicsComponent.hpp
//
#pragma once

// Forward declare
struct Mesh2d;
class GameObject;

struct Color {
	float red;
	float green;
	float blue;
};

class GraphicsComponent {
public:
	GraphicsComponent();

	GraphicsComponent (
		const Color & color,
		const Mesh2d * mesh
	);

	Color color;
	const Mesh2d * mesh;
};