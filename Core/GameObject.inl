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
	T * component = &componentPool->createComponent(*this);

	if (std::is_base_of<Script, T>::value) {
		// Register ComponentPool of derived Script types with ScriptSystem.
		ScriptSystem::addScriptPool(m_id, componentPool);
		reinterpret_cast<Script *>(component)->init();
	}

	return *component;
}

//---------------------------------------------------------------------------------------
template <class T>
T * GameObject::getComponent()
{
	assertIsDerivedFromComponent<T>();

	ComponentPool<T> * componentPool = ComponentPoolLocator<T>::getPool();
	return componentPool->getComponent(m_id);
}

//---------------------------------------------------------------------------------------
template <class T>
void GameObject::removeComponent()
{
	assertIsDerivedFromComponent<T>();

	ComponentPool<T> * componentPool = ComponentPoolLocator<T>::getPool();
	componentPool->destroyComponent(m_id);
}


#endif //_GAME_OBJECT_INL_