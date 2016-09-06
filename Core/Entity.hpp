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
	// All copied components are set to active by default.
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
	EntityID m_id;
	std::string m_name;
};



#include "Entity.inl"