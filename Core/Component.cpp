//
// Component.cpp
//
#include "Component.hpp"

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/GameObject.hpp"


//---------------------------------------------------------------------------------------
Component::Component()
	: m_gameObject(nullptr)
{

}

//---------------------------------------------------------------------------------------
Component::Component (
	const GameObject & gameObject
)
	: Entity(gameObject.getEntityID(), gameObject.getName()),
	  m_gameObject(const_cast<GameObject *>(&gameObject))
{

}

//---------------------------------------------------------------------------------------
Component::~Component()
{

}

//---------------------------------------------------------------------------------------
GameObject & Component::gameObject() const
{
	return *m_gameObject;
}

//---------------------------------------------------------------------------------------
Transform & Component::transform() const
{
	return *ComponentPoolLocator<Transform>::getPool()->getComponent(id);
}
