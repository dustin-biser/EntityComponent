//
// GameObject.cpp
//
#include "GameObject.hpp"

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/Transform.hpp"
#include "Rendering/Rendering.hpp"
#include "Physics/Physics.hpp"
#include "Motion/Motion.hpp"


//---------------------------------------------------------------------------------------
GameObject::GameObject(const std::string & name)
	: Entity(EntityID::generateID()),
	  name(name)
{
	ComponentPool<Transform> * transformPool = ComponentPoolLocator<Transform>::getPool();
	transformPool->createComponent(this->id, *this);
}

//---------------------------------------------------------------------------------------
Transform * GameObject::transform ()
{
	ComponentPool<Transform> * transformPool = ComponentPoolLocator<Transform>::getPool();
	return transformPool->getComponent (this->id);
}

//---------------------------------------------------------------------------------------
void GameObject::destroy()
{
	//-- Notify all ComponentPools to destroy Components associated with EnityID:
	ComponentPoolLocator<Transform>::getPool()->destroyComponent(this->id);
	ComponentPoolLocator<Rendering>::getPool()->destroyComponent(this->id);
	ComponentPoolLocator<Motion>::getPool()->destroyComponent(this->id);
	ComponentPoolLocator<Physics>::getPool()->destroyComponent(this->id);
	ComponentPoolLocator<Script>::getPool()->destroyComponent(this->id);
}
