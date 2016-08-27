//
// EntityID.cpp
//
#include "EntityID.hpp"

EntityID::id_type EntityID::currentId = 0;


const EntityID EntityID::NONE = EntityID(static_cast<id_type>(-1));



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
EntityID::EntityID()
	: value(NONE.value)
{

}

//---------------------------------------------------------------------------------------
EntityID EntityID::generateID()
{
	// Generate a new EntitID object and return it.
	return EntityID(EntityID::currentId++);
}

//---------------------------------------------------------------------------------------
bool EntityID::operator != (
	const EntityID & other
) const {
	return this->value != other.value;
}

//---------------------------------------------------------------------------------------
bool EntityID::operator == (
	const EntityID & other
) const {
	return this->value == other.value;
}

