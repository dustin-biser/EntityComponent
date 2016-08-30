//
// ComponentSystemLocator.inl
//
#ifndef _COMPONENT_SYSTEM_LOCATOR_INL_
#define _COMPONENT_SYSTEM_LOCATOR_INL_

#include "ComponentPoolLocator.hpp"

#include "Core/Utils.hpp"


// At program startup, determine set of all ComponentPool<T> types needed,
// and instantiate them.
template <class T>
ComponentPool<T> * ComponentPoolLocator<T>::requestedPool = new ComponentPool<T>();


//---------------------------------------------------------------------------------------
template <class T>
ComponentPool<T> * ComponentPoolLocator<T>::getPool()
{
	ASSERT(requestedPool);
	return requestedPool;
}

//---------------------------------------------------------------------------------------
template <class T>
ComponentPool<T> * ComponentPoolLocator<T>::provide (
	ComponentPool<T> * componentSystem
) {
	ComponentPool<T> * previousSystem = requestedPool;
	requestedPool = componentSystem;

	return previousSystem;
}



#endif //_COMPONENT_SYSTEM_LOCATOR_INL_