//
// PhysicsComponent.hpp
//
#pragma once

#include "vec2.hpp"


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