//
// PhysicsEventObserver.hpp
//
#pragma once

// Forward declare
class GameObject;
class PhysicsEvent;


// Abstract class
class PhysicsEventObserver {
public:
	virtual ~PhysicsEventObserver();

	virtual void onNotify (
		GameObject * gameObject,
		PhysicsEvent * physicsEvent
	) = 0;
};