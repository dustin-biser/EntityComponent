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
	~GameObject();

	// Returns a globally unique GameObjectID.
	static GameObjectID generateID();

	GameObjectID id;
	Transform transform;

	InputComponent * input;
	MotionComponent * motion;
	GraphicsComponent * graphics;
	PhysicsComponent * physics;

	void addChild (
		GameObject * child
	);

	GameObject * getChild (
		GameObjectID childID
	) const;

	// Returns the pool where this GameObject resides.
	GameObjectPool * getPool () const;

	struct ChildGameObject {
		GameObjectID id;
		GameObjectPool * residentPool;
	};
	std::vector<ChildGameObject> childObjects;


private:
	// Game Objects can only be created using GameObjectPools.
	friend class GameObjectPool;
	GameObject();

	void init (
		GameObjectID id,
		GameObjectPool * residentPool
	);

	// Pool where this GameObject is stored.
	GameObjectPool * residentPool;  
};
