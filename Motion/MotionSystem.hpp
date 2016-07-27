//
// MotionSystem.hpp
//
#pragma once

#if false

// Forward declare.
class GameObjectPool;
class MotionSystemImpl;

class MotionSystem {
public:
	MotionSystem();
	~MotionSystem();

	void update (
		GameObjectPool * gameObjectPool,
		float ellapsedTimeInSeconds
	);

private:
	MotionSystemImpl * impl;
};

#endif