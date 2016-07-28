//
// EntityID.cpp
//
#include "EntityID.hpp"

EntityID::id_type EntityID::currentId = 0;

//---------------------------------------------------------------------------------------
EntityID::EntityID (
	id_type value
) 
	: value(value)
{

}

//---------------------------------------------------------------------------------------
EntityID::EntityID (
	const EntityID & other
)
	: value(other.value)
{

}

//---------------------------------------------------------------------------------------
EntityID EntityID::generateID()
{
	// Generate a new EntitID object and return it.
	return EntityID(EntityID::currentId++);
}


