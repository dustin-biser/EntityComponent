//
// EntityID.cpp
//
#include "EntityID.hpp"

EntityID::id_value EntityID::currentId = 0;

//---------------------------------------------------------------------------------------
EntityID::EntityID (
	id_value value
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
EntityID::id_value EntityID::generateID()
{
	return currentId++;
}


