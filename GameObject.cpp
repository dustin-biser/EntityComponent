//
// GameObject.cpp
//
#include "GameObject.hpp"

GameObjectID GameObject::nextID = 0;

//---------------------------------------------------------------------------------------
GameObject::GameObject()
{

}

//---------------------------------------------------------------------------------------
GameObjectID GameObject::generateID()
{
	return nextID++;
}
