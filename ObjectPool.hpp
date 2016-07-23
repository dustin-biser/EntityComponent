//
// ObjectPool.hpp
//
#pragma once

typedef unsigned long EntityID;

// Forward declare.
template <class T, size_t NUM_OBJECTS>
class ObjectPoolImpl;


template <class T, size_t NUM_OBJECTS>
class ObjectPool {
public:
	ObjectPool();
	~ObjectPool();

	void create(EntityID id);

	void destroy(EntityID id);

	// Caution: calling ObjectPool::destory() will likely invalidate
	// pointer returned from this function.  
	// Call ObjectPool::getObject() after each call of ObjectPool::destory()
	// in order to keep pointer valid.
	T * getObject(EntityID id);

private:
	ObjectPoolImpl<T, NUM_OBJECTS> * impl;
};


#include "ObjectPool.inl"