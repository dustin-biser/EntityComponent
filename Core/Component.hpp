//
// Component.hpp
//
#pragma once

#include "Core/Entity.hpp"


// Forward declare
class GameObject;
class Transform;


// Base class for all Component types.
class Component : public Entity {
public:
	Component();

	Component (
		EntityID id,
		GameObject & gameObject
	);

	virtual ~Component();

	GameObject & gameObject() const;

	Transform & transform() const;


private:
	template <class T>
	friend class ComponentPoolImpl;
	friend class GameObject;

	union {
		GameObject * m_gameObject;

		// For use in forming a free list within ComponentPool.
		Component * next;
	};
};



#include <type_traits>

template <class T>
void assertIsDerivedFromComponent ()
{
	// Compile-time check
	static_assert(std::is_base_of<Component, T>::value,
		"T must be a type derived from class Component");
}

