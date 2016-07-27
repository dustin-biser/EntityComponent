//
// GameObject.inl
//
#ifndef _GAME_OBJECT_INL_
#define _GAME_OBJECT_INL_

#include "GameObject.hpp"


//---------------------------------------------------------------------------------------
template <class T>
void GameObject::addComponent()
{
	ComponentSystem<T> * system = ComponentSystemLocator<T>::getSystem();
	system->createComponent(id);
}

//---------------------------------------------------------------------------------------
template <class T>
SmartPointer<T> GameObject::getComponent()
{
	ComponentSystem<T> * system = ComponentSystemLocator<T>::getSystem();
	return system->getComponent(id);
}

#endif //_GAME_OBJECT_INL_