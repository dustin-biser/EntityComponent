//
// PhysicsComponent.hpp
//
#pragma once

#if false

#include "vec2.hpp"

#include "GameObject.hpp"

// Forward declare.
class PhysicsSystem;


struct BoundingBox {
	vec2 min;
	vec2 max;
};


class PhysicsComponent {
public:
	PhysicsComponent();

	virtual ~PhysicsComponent();

	PhysicsComponent * clone() const;

	BoundingBox boundingBox;
};

#endif