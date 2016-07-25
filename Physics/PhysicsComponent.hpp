//
// PhysicsComponent.hpp
//
#pragma once


#include "vec2.hpp"

class PhysicsComponent {
public:
	PhysicsComponent();

	virtual ~PhysicsComponent();

	PhysicsComponent * clone() const;

	struct BoundingBox {
		vec2 min;
		vec2 max;
	} boundingBox;
};