//
// Entity.cpp
//
#include "Entity.hpp"

//---------------------------------------------------------------------------------------
Entity::Entity (
	EntityID id,
	const std::string & name
)
	: m_id(id),
	  m_name(name)
{

}

//---------------------------------------------------------------------------------------
Entity::Entity()
	: m_id(EntityID::NONE)
{

}

//---------------------------------------------------------------------------------------
EntityID Entity::getEntityID() const
{
	return m_id;
}

//---------------------------------------------------------------------------------------
const std::string & Entity::getName() const
{
	return m_name;
}
