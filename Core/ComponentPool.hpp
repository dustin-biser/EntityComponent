//
// ComponentPool.hpp
//
#pragma once

#include "Core/EntityID.hpp"


// Forward declare.
template <class T>
class ComponentPoolImpl;
class GameObject;


// Memory pool that manages both an active-list and an inactive-list 
// of Components of type T.  Component objects are guaranteed to be tightly
// packed towards the beginning of their active/inactive lists.
template <class T>
class ComponentPool {
public:
	ComponentPool();
	~ComponentPool();

	T & createComponent (
		EntityID id,
		GameObject & gameObject
	);

	void destroyComponent (
		EntityID id
	);

	T & getComponent (
		EntityID id
	);

	void setComponentActive (
		EntityID id,
		bool activate
	);

	// Returns pointer to first element in the pool's active list.
	T * beginActive() const;

	// Returns the number of objects in active list.
	size_t numActive() const;


private:
	ComponentPoolImpl<T> * impl;
};


#include "ComponentPool.inl"
