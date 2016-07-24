//
// EntityPool.hpp
//
#pragma once

#include "EntityID.hpp"

// Forward declare.
template <class T, size_t NUM_OBJECTS>
class EntityPoolImpl;


// Type T must include a field named 'id' of type EntityID.
template <class T, size_t NUM_OBJECTS>
class EntityPool {
public:
	EntityPool();
	~EntityPool();

	T * create(EntityID id);

	// Caution: calling ObjectPool::destory() will likely invalidate
	// any pointers returned by ObjectPool.
	// Call ObjectPool::getObject() after each call of ObjectPool::destory()
	// in order to keep pointers valid.
	void destroy(EntityID id);

	T * getObject(EntityID id);

	// Return beginning of ObjectPool data.
	T * begin() const;

	// Returns the number of alive objects
	size_t numActive() const;

private:
	EntityPoolImpl<T, NUM_OBJECTS> * impl;
};


#include "EntityPool.inl"