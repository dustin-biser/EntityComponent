//
// PhysicsSystem.hpp
//
#pragma once

#if false

// Forward declare.
class GameObjectPool;
class PhysicsSystemImpl;


class PhysicsSystem {
public:
	PhysicsSystem();
	~PhysicsSystem();


	void update (
		GameObjectPool * gameObjectPool
	);

private:
	PhysicsSystemImpl * impl;

};

#endif
