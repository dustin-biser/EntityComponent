//
// ObjectPool.inl
//
#pragma once

#include "ObjectPool.hpp"

#include <vector>
using std::vector;

#include <cstring>
using std::memset;

#include <unordered_map>
using std::unordered_map;


template <class T>
struct FreeList {
	T * next;
};


template <class T, size_t NUM_OBJECTS>
class ObjectPoolImpl {
private:
	friend class ObjectPool<T, NUM_OBJECTS>;

	ObjectPoolImpl();

	size_t numActiveObjects();

	void create(EntityID id);

	void destroy(EntityID id);



	std::vector<T> pool;

	// Address of first available object for allocation.
	T * firstAvailable;

	// Up-to-date mapping from EntityID to memory address.
	std::unordered_map<EntityID, T *> idPointerMap;
};


//---------------------------------------------------------------------------------------
template <class T, size_t NUM_OBJECTS>
size_t ObjectPoolImpl<T, NUM_OBJECTS>::numActiveObjects()
{
	if (firstAvailable == nullptr) {
		return NUM_OBJECTS;
	} else {
		return size_t(firstAvailable - &pool[0]);
	}
}

//---------------------------------------------------------------------------------------
// Constructor
template <class T, size_t NUM_OBJECTS>
ObjectPoolImpl<T, NUM_OBJECTS>::ObjectPoolImpl()
	: pool(NUM_OBJECTS)
{
	if (sizeof(T) < sizeof(T *)) {
		// sizeof T must be large enough to use it's data as a next pointer
		// for FreeList.
		throw;
	}

	firstAvailable = &pool[0];

	// Set each T object equal memory address to next T object
	FreeList<T> * freeList;
	for (size_t i(0); i < NUM_OBJECTS - 1; ++i) {
		freeList = reinterpret_cast<FreeList<T> *>(&pool[i]);
		freeList->next = &pool[i + 1];
	}
	// Last T object points to nullptr.
	freeList = reinterpret_cast<FreeList<T> *>(&pool[NUM_OBJECTS - 1]);
	freeList->next = nullptr;
}

//---------------------------------------------------------------------------------------
template <class T, size_t NUM_OBJECTS>
ObjectPool<T, NUM_OBJECTS>::ObjectPool()
{
	impl = new ObjectPoolImpl<T, NUM_OBJECTS>();
}

//---------------------------------------------------------------------------------------
template <class T, size_t NUM_OBJECTS>
ObjectPool<T, NUM_OBJECTS>::~ObjectPool()
{
	delete impl;
	impl = nullptr;
}

//---------------------------------------------------------------------------------------
template <class T, size_t NUM_OBJECTS>
void ObjectPoolImpl<T, NUM_OBJECTS>::create (
	EntityID id
) {
	if (firstAvailable == nullptr) {
		// No space left in pool for allocation.
		throw;
	}

	T * newObject = firstAvailable;
	firstAvailable = reinterpret_cast<FreeList<T> *>(firstAvailable)->next;

	// For safety, zero out object's memory.
	memset(newObject, 0, sizeof(T));
	newObject->id = id;

	// Update idPointerMap
	idPointerMap[id] = newObject;
}

//---------------------------------------------------------------------------------------
template <class T, size_t NUM_OBJECTS>
void ObjectPoolImpl<T, NUM_OBJECTS>::destroy (
	EntityID id
) {
	size_t numActive = numActiveObjects();
	if (numActive == 0) {
		// No objects left to destroy.
		throw;
	}

	T * pObject = idPointerMap.at(id);

	// Swap pObject with last active in order to keep all
	// active objects in front of pool.
	{
		T * pLastActive = &pool[numActive - 1];

		// Update idPointerMap to moved destination
		idPointerMap[pLastActive->id] = pObject;

		std::swap(*pObject, *pLastActive);

		// Point to new location
		pObject = pLastActive;
	}


	// Set obj.next = firstAvailable.next
	reinterpret_cast<FreeList<T> *>(pObject)->next = firstAvailable;

	// obj is now the firstAvailable.
	firstAvailable = pObject;
}

//---------------------------------------------------------------------------------------
template <class T, size_t NUM_OBJECTS>
void ObjectPool<T, NUM_OBJECTS>::create(
	EntityID id
) {
	return impl->create(id);
}

//---------------------------------------------------------------------------------------
template <class T, size_t NUM_OBJECTS>
void ObjectPool<T, NUM_OBJECTS>::destroy (
	EntityID id
) {
	impl->destroy(id);
}

//---------------------------------------------------------------------------------------
template <class T, size_t NUM_OBJECTS>
T * ObjectPool<T, NUM_OBJECTS>::getObject (
	EntityID id
) {
	return impl->idPointerMap.at(id);

}



