//
// GameObject.hpp
//
#pragma once

#include <string>

#include "Core/Entity.hpp"

// Forward declare.
class Transform;


// Base class for all game related objects.
// Every GameObject includes a string name and a Transform Component.
class GameObject : public Entity {
public:
	GameObject (const std::string & name);

	GameObject (const GameObject & other);

	// Add Component to GameObject.
	template <class T>
	T & addComponent();

	// Removes Component of type T so that it is no longer associated
	// with GameObject.
	template <class T>
	void removeComponent();

	// Returns a pointer to the GameObject's type T Component.
	// Returns nullptr if GameObject does not have a Component of type T.
	template <class T>
	T * getComponent();


	// Activate/deactivate GameObject.
	void setActive(bool status);


	// Convenience method to retrieve the GameObject's Transform Component.
	Transform & transform () const;


	// Destroys GameObject and all associated Components.
	void destroy();
};


#include "GameObject.inl"