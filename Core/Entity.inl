//
// Entity.inl
//
#ifndef _ENTITY_INL_
#define _ENTITY_INL_

#include "Entity.hpp"

//#include "Core/GameObject.hpp"


//---------------------------------------------------------------------------------------
template <class T>
/*static*/
typename std::enable_if<std::is_same<GameObject, T>::value,
T &>::type Entity::replicate (
	const T & other
) {
	GameObject * gameObject = new GameObject(other); // Copies all components
	return *gameObject;
}

//---------------------------------------------------------------------------------------
template <class T>
/*static*/ 
typename std::enable_if<!std::is_same<GameObject, T>::value,
T &>::type Entity::replicate (
	const T & other
) {
	GameObject * gameObject = new GameObject(other.name);
	T & newEntity = gameObject->addComponent<T>();

	// Clone child Transforms
	gameObject->transform() = other.transform();

	return newEntity;
}

#endif //_ENTITY_INL_
