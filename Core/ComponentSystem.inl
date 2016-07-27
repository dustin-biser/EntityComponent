//
// ComponentSystem.inl
//
#ifndef _COMPONENT_SYSTEM_INL_
#define _COMPONENT_SYSTEM_INL_

#include "ComponentSystem.hpp"

#include "Core/Component.hpp"

//---------------------------------------------------------------------------------------
template <class T>
ComponentSystem<T>::ComponentSystem()
{
	// Compile-time sanity check
	static_assert(std::is_base_of<Component, T>::value,
		"T must be a type derived from class Component");
}


//---------------------------------------------------------------------------------------
template <class T>
void ComponentSystem<T>::createComponent(EntityID id)
{

}

//---------------------------------------------------------------------------------------
template <class T>
SmartPointer<T> ComponentSystem<T>::getComponent(EntityID id)
{

}


#endif //_COMPONENT_SYSTEM_INL_
