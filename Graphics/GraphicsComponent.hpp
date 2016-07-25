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

	virtual ~GraphicsComponent();

	GraphicsComponent (
		const Color & color,
		const Mesh2d * mesh
	);

	virtual GraphicsComponent * clone() const;

	Color color;
	const Mesh2d * mesh;
};