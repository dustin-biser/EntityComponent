//
// GameObjectReplicator.hpp
//
#pragma once

// Forward declare.
class GameObject;
class GameObjectPool;
class GameObjectReplicatorImpl;


// Class for generating copies of a prototype GameObject.
//
// All newly created GameObjectsbjects will be allocated in the
// provided allocationPool.
class GameObjectReplicator {
public:
	GameObjectReplicator (
		GameObject * prototype
	);

	~GameObjectReplicator();

	GameObject * replicateInto(GameObjectPool * allocationPool);

	void setPrototype(GameObject * prototype);

	GameObject * getPrototype() const;


private:
	GameObjectReplicatorImpl * impl;
};
