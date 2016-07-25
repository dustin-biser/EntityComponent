//
// MotionComponent.hpp
//
#pragma once

#include "vec2.hpp"

class GameObject;


class MotionComponent {
public:
	MotionComponent();

	virtual ~MotionComponent();

	virtual MotionComponent * clone() const;

	virtual void update (
		GameObject * gameObject,
		float elapsedTime
	);

	vec2 velocity;
};