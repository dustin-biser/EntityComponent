//
// GameObject.cpp
//
#include "GameObject.hpp"

//---------------------------------------------------------------------------------------
GameObject::GameObject () 
{

}

//---------------------------------------------------------------------------------------
void GameObject::init (
	GameObjectID id,
	GameObjectPool * residentPool
) {
	this->id = id;
	this->residentPool = residentPool;
}

//---------------------------------------------------------------------------------------
GameObjectID GameObject::generateID()
{
	static GameObjectID nextID = 0;
	return nextID++;
}
