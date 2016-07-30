//
// ClockHandMotionComponent.hpp
//
#pragma once

#if false

#include "Motion.hpp"

// Forward declare.
class GameObject;


class ClockHandMotionComponent : public Motion {
public:
	virtual Motion * clone() const;

	virtual void update (
		GameObject * gameObject,
		float elapsedTime
	);
};

#endif