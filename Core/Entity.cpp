//
// Entity.cpp
//
#include "Entity.hpp"

//---------------------------------------------------------------------------------------
Entity::Entity(EntityID id)
	: id(id)
{

}

//---------------------------------------------------------------------------------------
EntityID Entity::getEntityID() const
{
	return id;
}
