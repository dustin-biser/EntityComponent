//
// EntityID.hpp
//
#pragma once

class EntityID {
public:
	typedef unsigned long id_value;

	explicit EntityID (id_value value);

	EntityID (const EntityID & other);


	static id_value generateID();


	EntityID & operator = (const EntityID & other) = delete;
	EntityID & operator = (const EntityID && other) = delete;

	id_value value;

private:
	static id_value currentId;
};
