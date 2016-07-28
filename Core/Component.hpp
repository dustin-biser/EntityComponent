//
// Component.hpp
//
#pragma once

#include "Core/Entity.hpp"

// Forward declare
class GameObject;
template <class T>
class ComponentPool;



// Base class for all Component types.
class Component : public Entity {
public:
	Component (
		EntityID id,
		GameObject & gameObject
	);

	virtual ~Component();

	Component * operator -> () const;

	Component & operator * () const;

	GameObject & gameObject;



private:
	template <class T>
	friend class ComponentPool;

	void updatePointerTableEntry (
		Component * newAddress
	);

	size_t pointerTableIndex;
};