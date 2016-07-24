//
// GameObjectPool.cpp
//
#include "GameObjectPool.hpp"

#include <unordered_map>
using std::unordered_map;


struct FreeList {
	GameObject * next;
};


class GameObjectPoolImpl {
private:
	friend class GameObjectPool;

	GameObjectPoolImpl (
		GameObject * pool,
		size_t numElements
	);

	size_t numActiveObjects();

	GameObject * create(GameObjectID id);

	void destroy(GameObjectID id);


	GameObject * pool;
	const size_t numPoolElements;

	// Address of first available object for allocation.
	GameObject * firstAvailable;

	// Up-to-date mapping from EntityID to memory address.
	std::unordered_map<GameObjectID, GameObject *> idPointerMap;
};


//---------------------------------------------------------------------------------------
size_t GameObjectPoolImpl::numActiveObjects()
{
	if (firstAvailable == nullptr) {
		return numPoolElements;
	}
	else {
		return size_t(firstAvailable - &pool[0]);
	}
}

//---------------------------------------------------------------------------------------
// Constructor
GameObjectPoolImpl::GameObjectPoolImpl(
	GameObject * pool,
	size_t numElements
)
	: pool(pool),
	  numPoolElements(numElements)
{
	firstAvailable = &pool[0];

	// Set each T object equal memory address to next T object
	FreeList * freeList;
	size_t lastPoolIndex = numPoolElements - 1;
	for (size_t i(0); i < lastPoolIndex; ++i) {
		freeList = reinterpret_cast<FreeList *>(&pool[i]);
		freeList->next = &pool[i + 1];
	}
	// Last T object points to nullptr.
	freeList = reinterpret_cast<FreeList *>(&pool[lastPoolIndex]);
	freeList->next = nullptr;
}

//---------------------------------------------------------------------------------------
GameObjectPool::GameObjectPool(
	size_t numElements
)
{
	GameObject * pool = new GameObject[numElements];
	impl = new GameObjectPoolImpl(pool, numElements);
}

//---------------------------------------------------------------------------------------
GameObjectPool::~GameObjectPool()
{
	// Free pool resources.
	GameObject * pool = impl->pool;
	delete[] pool; // Calls destructor on all GameObjects.

	delete impl;
	impl = nullptr;
}

//---------------------------------------------------------------------------------------
GameObject * GameObjectPoolImpl::create (
	GameObjectID id
) {
	if (firstAvailable == nullptr) {
		// No space left in pool for allocation.
		throw;
	}

	GameObject * result = firstAvailable;
	firstAvailable = reinterpret_cast<FreeList *>(firstAvailable)->next;

	// Update idPointerMap
	idPointerMap[id] = result;

	return result;
}

//---------------------------------------------------------------------------------------
void GameObjectPoolImpl::destroy (
	GameObjectID id
)
{
	size_t numActive = numActiveObjects();
	if (numActive == 0) {
		// No objects left to destroy.
		throw;
	}

	GameObject * pObject = idPointerMap.at(id);

	// Call destructor GameObject
	pObject->~GameObject();

	// Remove unused id
	idPointerMap.erase(id);

	// Swap pObject with last active in order to keep all
	// active objects in front of pool.
	GameObject * pLastActive = &pool[numActive - 1];
	if (pLastActive != pObject) {
		// Update idPointerMap to moved destination
		idPointerMap[pLastActive->id] = pObject;

		std::swap(*pObject, *pLastActive);

		// Point to new location
		pObject = pLastActive;
	}

	// Set obj.next = firstAvailable.next
	reinterpret_cast<FreeList *>(pObject)->next = firstAvailable;

	// obj is now the firstAvailable.
	firstAvailable = pObject;
}

//---------------------------------------------------------------------------------------
GameObject * GameObjectPool::create (
	GameObjectID id
) {
	GameObject * location = impl->create(id);

	// Place object at location and call constructor.
	GameObject * newObject = new (location) GameObject();

	// Update GameObject fields
	newObject->init(id, this);

	return newObject;
}

//---------------------------------------------------------------------------------------
void GameObjectPool::destroy(
	GameObjectID id
) {
	impl->destroy(id);
}

//---------------------------------------------------------------------------------------
GameObject * GameObjectPool::getObject(
	GameObjectID id
)
{
	return impl->idPointerMap.at(id);
}

//---------------------------------------------------------------------------------------
GameObject * GameObjectPool::begin() const
{
	return impl->pool;
}

//---------------------------------------------------------------------------------------
size_t GameObjectPool::numActive() const
{
	return impl->numActiveObjects();
}
