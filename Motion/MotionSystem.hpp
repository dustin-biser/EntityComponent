//
// MotionSystem.hpp
//
#pragma once

#if false

// Forward declare.
class ComponentPool;
class MotionSystemImpl;

class MotionSystem {
public:
	MotionSystem();
	~MotionSystem();

	void update (
		ComponentPool * gameObjectPool,
		float ellapsedTimeInSeconds
	);

private:
	MotionSystemImpl * impl;
};

#endif