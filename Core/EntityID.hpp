//
// EntityID.hpp
//
#pragma once

class EntityID {
public:
	typedef unsigned long id_type;

	EntityID();

	explicit EntityID (id_type value);

	EntityID (const EntityID & other);

	// Generates a new globally unique EntityID.
	static EntityID generateID();

	bool operator == (const EntityID & other) const;

	bool operator != (const EntityID & other) const;


	id_type value;

	static const EntityID NO_ENTITY;


private:
	static id_type currentId;
};
