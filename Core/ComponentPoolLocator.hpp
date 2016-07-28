//
// ComponentSystemLocator.hpp
//
#pragma once

// Forward declare
template <class T>
class ComponentPool;


// Service Locater class for providing access to a ComponentPool<T> instance.
template <class T>
class ComponentPoolLocator {
public:
	static ComponentPool<T> * getPool();

	// Returns previously registered pool.
	static ComponentPool<T> * provide(ComponentPool<T> * componentPool);

private:
	static ComponentPool<T> * requestedPool;

};


#include "ComponentPoolLocator.inl"