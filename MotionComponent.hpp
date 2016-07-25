//
// MotionComponent.hpp
//
#pragma once

#include "vec2.hpp"

class MotionComponent {
public:
	virtual ~MotionComponent();

	virtual MotionComponent * clone() const;

	vec2 velocity;
};