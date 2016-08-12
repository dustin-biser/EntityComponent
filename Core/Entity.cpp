//
// Entity.cpp
//
#include "Entity.hpp"

//---------------------------------------------------------------------------------------
Entity::Entity (
	EntityID id,
	const std::string & name
)
	: id(id),
	  name(name)
{

}

//---------------------------------------------------------------------------------------
Entity::Entity()
	: id(EntityID::NO_ENTITY)
{

}

//---------------------------------------------------------------------------------------
EntityID Entity::getEntityID() const
{
	return id;
}

//---------------------------------------------------------------------------------------
const std::string & Entity::getName() const
{
	return name;
}
