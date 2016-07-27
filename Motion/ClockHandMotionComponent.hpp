//
// ClockHandMotionComponent.hpp
//
#pragma once

#if false

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

#endif