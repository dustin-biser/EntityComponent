//
// GameObject.inl
//
#ifndef _GAME_OBJECT_INL_
#define _GAME_OBJECT_INL_

#include "GameObject.hpp"
#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/Transform.hpp"

#include "Script/Script.hpp"
#include "Rendering/Rendering.hpp"

#include <type_traits>

//---------------------------------------------------------------------------------------
template <class T>
T * GameObject::addComponent()
{
	assertIsDerivedFromComponent<T>();

	if (std::is_base_of<Script, T>::value) {
		Script * pScript = reinterpret_cast<Script *>(new T (this->id, *this));

		ComponentPool<Script> * componentPool = ComponentPoolLocator<Script>::getPool();
		Script * derivedScript = componentPool->createComponent(id, *this);
		derivedScript->scriptBehavior = pScript;
	}
	else {
		ComponentPool<T> * componentPool = ComponentPoolLocator<T>::getPool();
		return componentPool->createComponent(id, *this);
	}
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