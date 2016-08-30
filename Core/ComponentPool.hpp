//
// ComponentPool.hpp
//
#pragma once

#include "Core/ComponentPoolBase.hpp"

// Forward declare.
template <class T>
class ComponentPoolImpl;
class GameObject;
class EntityID;
class Component;


// Memory pool that manages both an active-list and an inactive-list 
// of Components of type T.  Component objects are guaranteed to be tightly
// packed towards the beginning of their active/inactive lists.
template <class T>
class ComponentPool : public ComponentPoolBase {
public:
	ComponentPool();
	~ComponentPool();

	T * getComponent (
		const EntityID & id
	) const;

	// Allocates Component and returns a pointer to it.
	T & createComponent (
		const GameObject & gameObject
	);

	// Allocates Component.
	void allocateComponent (
		const GameObject & gameObject
	) override;

	void destroyComponent (
		const EntityID & id
	) override;

	void setActive (
		const EntityID & id,
		bool activeStatus
	) override;

	// Returns true if ComponentPool contains a Component with 
	// the given EntityID.
	bool hasComponent (
		const EntityID & id
	) const override;

	// Returns pointer to first element in the pool's active list.
	T * beginActive() const;

	// Returns the number of objects in active list.
	size_t numActive() const override;

	Component * operator [] (int index) const override;


private:
	ComponentPoolImpl<T> * impl;
};

#include "ComponentPool.inl"
