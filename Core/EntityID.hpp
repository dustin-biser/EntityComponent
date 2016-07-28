//
// EntityID.hpp
//
#pragma once

class EntityID {
public:
	typedef unsigned long id_type;

	explicit EntityID (id_type value);

	EntityID (const EntityID & other);


	// Generates a new globally unique EntityID.
	static EntityID generateID();


	EntityID & operator = (const EntityID & other) = delete;
	EntityID & operator = (const EntityID && other) = delete;

	id_type value;

private:
	static id_type currentId;
};
