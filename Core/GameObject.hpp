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

	// Adds a new Component of type T to the calling GameObject and 
	// returns a pointer to the Component. If Component of type T already
	// exists for GameObject, then a pointer to it is returned without
	// adding a new Component.
	template <class T>
	T * addComponent();

	// Removes Component of type T so that it is no longer associated
	// with this GameObject.
	template <class T>
	void removeComponent();

	// Returns a pointer to an existing Component of type T.
	template <class T>
	T * getComponent();


	void setActive(bool status);


	// Convenience method to retrieve the GameObject's Transform Component.
	Transform * transform ();


	void destroy();


	const std::string name;
};


#include "GameObject.inl"