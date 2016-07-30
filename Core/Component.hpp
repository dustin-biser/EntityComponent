//
// Component.hpp
//
#pragma once

#include "Core/Entity.hpp"


// Forward declare
class GameObject;


// Base class for all Component types.
class Component : public Entity {
public:
	Component (
		EntityID id,
		GameObject & gameObject
	);

	virtual ~Component();

	GameObject & gameObject() const;


private:
	GameObject * m_gameObject;
};



#include <type_traits>

template <class T>
void assertIsDerivedFromComponent ()
{
	// Compile-time check
	static_assert(std::is_base_of<Component, T>::value,
		"T must be a type derived from class Component");
}

