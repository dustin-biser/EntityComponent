//
// GameObject.hpp
//
#pragma once

#include <string>

#include "Core/Entity.hpp"

// Forward declare.
class Transform;


// Base class for all game related objects.
// Every GameObject includes a name and a transform.
class GameObject : public Entity {
public:
	GameObject (const std::string & name);

	// Creates a new Component of type T and returns a pointer to it.
	template <class T>
	T * addComponent();

	// Returns a pointer to an existing Component of type T.
	template <class T>
	T * getComponent();

	const std::string name;

	Transform * transform;
};


#include "GameObject.inl"