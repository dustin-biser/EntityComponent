//
// GameObject.inl
//
#ifndef _GAME_OBJECT_INL_
#define _GAME_OBJECT_INL_

#include "GameObject.hpp"

#include "Core/Component.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/ComponentPoolLocator.hpp"

#include "Script/Script.hpp"
#include "Script/ScriptSystem.hpp"


//---------------------------------------------------------------------------------------
template <class T>
T & GameObject::addComponent()
{
	assertIsDerivedFromComponent<T>();

	ComponentPool<T> * componentPool = ComponentPoolLocator<T>::getPool();

	if (std::is_base_of<Script, T>::value) {
		// Add ComponentPool of derived Script types to ScriptSystem.
		ScriptSystem::addScriptPool(componentPool);
	}

	return componentPool->createComponent(*this);
}

//---------------------------------------------------------------------------------------
template <class T>
T * GameObject::getComponent()
{
	assertIsDerivedFromComponent<T>();

	ComponentPool<T> * componentPool = ComponentPoolLocator<T>::getPool();
	return componentPool->getComponent(id);
}

//---------------------------------------------------------------------------------------
template <class T>
void GameObject::removeComponent()
{
	assertIsDerivedFromComponent<T>();

	ComponentPool<T> * componentPool = ComponentPoolLocator<T>::getPool();
	componentPool->destroyComponent(this->id);
}


#endif //_GAME_OBJECT_INL_