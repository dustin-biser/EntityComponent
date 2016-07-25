//
// GameObject.hpp
//
#pragma once

#include <vector>
#include "Transform.hpp"


// Forward declare
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

	void clone(const GameObject & other);

	struct ChildGameObject {
		GameObjectID id;
		GameObjectPool * residentPool;
	};
	std::vector<ChildGameObject> childObjects;


private:
	// GameObjects can only be created through these classes: 
	friend class GameObjectPool;
	friend class GameObjectReplicator;
	GameObject();

	void init (
		GameObjectID id,
		GameObjectPool * residentPool
	);

	// Pool where this GameObject is stored.
	GameObjectPool * residentPool;  
};
