//
// Component.cpp
//

#include "Component.hpp"

#include "Core/Transform.hpp"
#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"


//---------------------------------------------------------------------------------------
Component::Component (
	EntityID id,
	GameObject & gameObject
) 
	: Entity(id),
	  m_gameObject(&gameObject)
{

}

//---------------------------------------------------------------------------------------
Component::Component()
	: m_gameObject(nullptr)
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
	return ComponentPoolLocator<Transform>::getPool()->getComponent(id);
}
