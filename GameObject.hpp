//
// GameObject.hpp
//
#pragma once

#include <vector>
#include "Transform.hpp"


// Forward declare
class InputComponent;
class MotionComponent;
class GraphicsComponent;
class PhysicsComponent;
class GameObjectPool;


typedef unsigned long GameObjectID;


class GameObject {
public:
	static GameObjectID generateID();

	GameObjectID id;
	Transform transform;

	InputComponent * input;
	MotionComponent * motion;
	GraphicsComponent * graphics;
	PhysicsComponent * physics;

	std::vector<GameObject *> childObjects;


private:
	// Game Objects can only be created using GameObjectPools.
	friend class GameObjectPool;
	GameObject();

	void init(GameObjectID id, GameObjectPool * residentPool);

	const GameObjectPool * residentPool;
};
