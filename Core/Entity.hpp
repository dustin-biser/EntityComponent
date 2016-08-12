//
// Entity.hpp
//
#pragma once

#include "Core/EntityID.hpp"

#include <string>
#include <type_traits>

// Forward declare.
class GameObject;


// Base class for all stateful objects within game.
class Entity {
public:
	Entity();

	Entity (
		EntityID id,
		const std::string & name
	);

	EntityID getEntityID() const;

	const std::string & getName() const;


	// Replicates a GameObject Entity and returns a reference to the new copy.
	template <class T>
	static 
	typename std::enable_if<std::is_same<GameObject, T>::value,
	T &>::type replicate (const T & other);

	// Replicates a non-GameObject Entity and returns a reference to the new copy.
	template <class T>
	static 
	typename std::enable_if<!std::is_same<GameObject, T>::value,
	T &>::type replicate (const T & other);


protected:
	EntityID id;
	std::string name;
};



#include "Entity.inl"