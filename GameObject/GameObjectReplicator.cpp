//
// GameObjectReplicator.cpp
//

#include "GameObjectReplicator.hpp"
#include "GameObject.hpp"
#include "GameObjectPool.hpp"

class GameObjectReplicatorImpl {
private:
	friend class GameObjectReplicator;

	GameObjectReplicatorImpl (
		GameObjectID prototypeId,
		GameObjectPool * prototypePool
	);

	// Data needed to retrieve prototype GameObject
	GameObjectID prototypeId;
	GameObjectPool * prototypePool;
};

//---------------------------------------------------------------------------------------
GameObjectReplicatorImpl::GameObjectReplicatorImpl(
	GameObjectID prototypeId,
	GameObjectPool * prototypePool
)
	: prototypeId(prototypeId),
	  prototypePool(prototypePool)
{

}

//---------------------------------------------------------------------------------------
GameObjectReplicator::GameObjectReplicator (
	GameObject * prototype
) {
	impl = new GameObjectReplicatorImpl (
		prototype->id, prototype->getPool()
	);
}

//---------------------------------------------------------------------------------------
GameObjectReplicator::~GameObjectReplicator()
{
	delete impl;
	impl = nullptr;
}

//---------------------------------------------------------------------------------------
GameObject * GameObjectReplicator::replicateTo (
	GameObjectPool * allocationPool
) {
	GameObject * newObject = allocationPool->create(GameObject::generateID());

	GameObject * prototype = impl->prototypePool->getObject(impl->prototypeId);

	newObject->clone(*prototype);

	return newObject;
}

//---------------------------------------------------------------------------------------
GameObject * GameObjectReplicator::getPrototype() const
{
	GameObjectPool * prototypePool = impl->prototypePool;
	return prototypePool->getObject(impl->prototypeId);
}

