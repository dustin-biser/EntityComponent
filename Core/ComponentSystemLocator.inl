//
// ComponentSystemLocator.inl
//
#ifndef _COMPONENT_SYSTEM_LOCATOR_INL_
#define _COMPONENT_SYSTEM_LOCATOR_INL_

#include "ComponentSystemLocator.hpp"

#include <cassert>


template <class T>
ComponentSystem<T> * ComponentSystemLocator<T>::requestedService = new ComponentSystem<T>();


//---------------------------------------------------------------------------------------
template <class T>
ComponentSystem<T> * ComponentSystemLocator<T>::getSystem()
{
	assert(requestedService);
	return requestedService;
}

//---------------------------------------------------------------------------------------
template <class T>
ComponentSystem<T> * ComponentSystemLocator<T>::provide (
	ComponentSystem<T> * componentSystem
) {
	ComponentSystem<T> * previousSystem = requestedService;
	requestedService = componentSystem;

	return previousSystem;
}



#endif //_COMPONENT_SYSTEM_LOCATOR_INL_