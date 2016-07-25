//
// ClockHandMotionComponent.hpp
//
#pragma once

#include "MotionComponent.hpp"

// Forward declare.
class GameObject;


class ClockHandMotionComponent : public MotionComponent {
public:
	virtual MotionComponent * clone() const;

	virtual void update (
		GameObject * gameObject,
		float elapsedTime
	);
};
