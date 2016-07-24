//
// GameObject.cpp
//
#include "GameObject.hpp"

//---------------------------------------------------------------------------------------
GameObject::GameObject () 
{

}

//---------------------------------------------------------------------------------------
GameObjectID GameObject::generateID()
{
	static GameObjectID nextID = 0;
	return nextID++;
}
