//
// GameObject.hpp
//
#pragma once

#include <string>

#include "Core/Entity.hpp"

// Forward declare.
class Transform;
class Component;
class Script;


// Base class for all game related objects.
// Every GameObject includes a string name and a Transform Component.
class GameObject : public Entity {
public:
	GameObject (const std::string & name);

	// For adding Non-Script Components.
	template <class T>
	typename std::enable_if<
		std::is_base_of<Component, T>::value &&
		!std::is_base_of<Script, T>::value, 
	T &>::type
	addComponent();


	// For adding Script Components.
	template <class T>
	typename std::enable_if<
		std::is_base_of<Component, T>::value &&
		std::is_base_of<Script, T>::value, 
	T &>::type
	addComponent();


	// Removes Component of type T so that it is no longer associated
	// with this GameObject.
	template <class T>
	void removeComponent();

	// Returns a reference to an existing Component of type T.
	template <class T>
	T & getComponent();


	void setActive(bool status);


	// Convenience method to retrieve the GameObject's Transform Component.
	Transform & transform ();


	void destroy();


	const std::string name;
};


#include "GameObject.inl"