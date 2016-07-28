//
// GameObject.cpp
//
#include "GameObject.hpp"

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/Transform.hpp"


//---------------------------------------------------------------------------------------
GameObject::GameObject(const std::string & name)
	: Entity(EntityID::generateID()),
	  name(name)
{
	ComponentPool<Transform> * transformPool = ComponentPoolLocator<Transform>::getPool();
	transform = transformPool->createComponent(this->id, *this);
}
