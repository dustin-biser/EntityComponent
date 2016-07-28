//
// GameObject.inl
//
#ifndef _GAME_OBJECT_INL_
#define _GAME_OBJECT_INL_

#include "GameObject.hpp"
#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/Transform.hpp"


//---------------------------------------------------------------------------------------
template <class T>
T * GameObject::addComponent()
{
	// Compile-time check
	static_assert(std::is_base_of<Component, T>::value,
		"T must be a type derived from class Component");

	ComponentPool<T> * componentPool = ComponentPoolLocator<T>::getPool();
	return componentPool->createComponent(id, *this);
}

//---------------------------------------------------------------------------------------
template <class T>
T * GameObject::getComponent()
{
	// Compile-time check
	static_assert(std::is_base_of<Component, T>::value,
		"T must be a type derived from class Component");

	ComponentPool<T> * componentPool = ComponentPoolLocator<T>::getPool();
	return componentPool->getComponent(id);
}

#endif //_GAME_OBJECT_INL_