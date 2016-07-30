//
// Component.cpp
//

#include "Component.hpp"


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
Component::~Component()
{

}

//---------------------------------------------------------------------------------------
GameObject & Component::gameObject() const
{
	return *m_gameObject;
}
