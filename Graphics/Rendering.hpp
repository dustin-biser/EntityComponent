//
// Material.hpp
//
#pragma once

#include "Core/Component.hpp"

// Forward declare
struct Mesh2d;
class GameObject;

struct Color {
	float red;
	float green;
	float blue;
};

class Rendering : public Component {
public:
	Rendering (
		EntityID id,
		GameObject & gameObject
	);

	virtual ~Rendering();

	virtual Rendering * clone() const;

	Color color;
	const Mesh2d * mesh;
};