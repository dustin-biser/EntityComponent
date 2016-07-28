//
// PhysicsSystem.hpp
//
#pragma once

#if false

// Forward declare.
class ComponentPool;
class PhysicsSystemImpl;


class PhysicsSystem {
public:
	PhysicsSystem();
	~PhysicsSystem();


	void update (
		ComponentPool * gameObjectPool
	);

private:
	PhysicsSystemImpl * impl;

};

#endif
