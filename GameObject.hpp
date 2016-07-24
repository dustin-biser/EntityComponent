//
// GameObject.hpp
//
#pragma once

#include <vector>
#include "TransformComponent.hpp"


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
	TransformComponent transform;

	InputComponent * input;
	MotionComponent * motion;
	GraphicsComponent * graphics;
	PhysicsComponent * physics;

	std::vector<GameObject *> childObjects;


private:
	// Game Objects can only be created using GameObjectPools.
	friend class GameObjectPool;
	GameObject();

	const GameObjectPool * residentPool;
};
