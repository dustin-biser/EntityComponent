//
// Script.inl
//
#ifndef _SCRIPT_INL_
#define _SCRIPT_INL_

#include "Script.hpp"

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/GameObject.hpp"

//---------------------------------------------------------------------------------------
template <class T>
/*static*/
typename std::enable_if<std::is_base_of<Script, T>::value,
T &>::type Script::replicate (
	const T & other
) {
	// Allocate new GameObject to be associated with T Script.
	GameObject * gameObject = new GameObject(other.name);
	ComponentPool<T> * componentPool = ComponentPoolLocator<T>::getPool();
	T & newScript = componentPool->createComponent(*gameObject);
	newScript = other;

	return newScript;
}


#endif //_SCRIPT_INL_