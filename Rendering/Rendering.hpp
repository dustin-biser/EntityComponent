//
// Material.hpp
//
#pragma once

#include "Assets/Mesh2d.hpp"
#include "Core/Component.hpp"


// Forward declare
struct Mesh2d;
class GameObject;

struct Color {
	float red;
	float green;
	float blue;
};

class Rendering final : public Component {
public:
	Rendering();

	Rendering (
		EntityID id,
		GameObject & gameObject
	);

	Color color;
	const Mesh2d * mesh;


private:
	Mesh2d defaultMesh;
};