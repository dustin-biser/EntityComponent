//
// EntityID.cpp
//
#include "EntityID.hpp"

EntityID::id_type EntityID::currentId = 0;


const EntityID EntityID::NO_ENTITY = EntityID(static_cast<id_type>(-1));



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
	: value(NO_ENTITY.value)
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

//---------------------------------------------------------------------------------------
void EntityID::clear()
{
	this->value = EntityID::NO_ENTITY.value;
}

