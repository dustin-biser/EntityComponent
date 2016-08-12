//
// GameObject.cpp
//
#include "GameObject.hpp"

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/EntityID.hpp"
#include "Core/Transform.hpp"

#include "Motion/Motion.hpp"

#include "Physics/Physics.hpp"

#include "Rendering//Rendering.hpp"

#include "Script/Script.hpp"
#include "Script/ScriptSystem.hpp"


//---------------------------------------------------------------------------------------
GameObject::GameObject(const std::string & name)
	: Entity(EntityID::generateID(), name) // Generate a new EntityID
{
	// Create Transform to be associated with GameObject.
	ComponentPool<Transform> * transformPool = ComponentPoolLocator<Transform>::getPool();
	transformPool->createComponent(*this);
}

//---------------------------------------------------------------------------------------
GameObject::GameObject(const GameObject & other)
	: Entity(EntityID::generateID(), other.name) // Generate a new EntityID
{
	const EntityID otherID = other.id;

	ComponentPool<Transform> * transformPool = ComponentPoolLocator<Transform>::getPool();
	Transform & transform = transformPool->createComponent(*this);
	transform = other.transform();

	ComponentPool<Rendering> * renderingPool = ComponentPoolLocator<Rendering>::getPool();
	Rendering * otherRendering = renderingPool->getComponent(otherID);
	if (otherRendering) {
		Rendering & newRendering = renderingPool->createComponent(*this);
		newRendering = *otherRendering;
	}

	ComponentPool<Motion> * motionPool = ComponentPoolLocator<Motion>::getPool();
	Motion * otherMotion = motionPool->getComponent(otherID);
	if (otherMotion) {
		Motion & newMotion = motionPool->createComponent(*this);
		newMotion = *otherMotion;
	}

	ComponentPool<Physics> * physicsPool = ComponentPoolLocator<Physics>::getPool();
	Physics * otherPhysics = physicsPool->getComponent(otherID);
	if (otherPhysics) {
		Physics & newPhysics = physicsPool->createComponent(*this);
		newPhysics = *otherPhysics;
	}

	ComponentPoolBase ** scriptComponentPool = ScriptSystem::getScriptPoolsBegin();
	for (size_t i(0); i < ScriptSystem::numScriptPools(); ++i) {
		if (scriptComponentPool[i]->hasComponent(otherID)) {
			scriptComponentPool[i]->allocateComponent(*this);
			break;
		}
	}

}

//---------------------------------------------------------------------------------------
void GameObject::setActive (
	bool status
) {
	//-- Notify ComponentPools to deactivate Components associated with EnityID:
	ComponentPoolLocator<Transform>::getPool()->setComponentActive(this->id, status);
	ComponentPoolLocator<Rendering>::getPool()->setComponentActive(this->id , status);
	ComponentPoolLocator<Motion>::getPool()->setComponentActive(this->id, status);
	ComponentPoolLocator<Physics>::getPool()->setComponentActive(this->id, status);

	// TODO - Use ScriptSystem to call setComponentActive from all ScriptPools.
	ComponentPoolLocator<Script>::getPool()->setComponentActive(this->id, status);
}

//---------------------------------------------------------------------------------------
Transform & GameObject::transform () const
{
	return *ComponentPoolLocator<Transform>::getPool()->getComponent(this->id);
}

//---------------------------------------------------------------------------------------
void GameObject::destroy()
{
	//-- Notify ComponentPools to destroy Components associated with EnityID:
	ComponentPoolLocator<Transform>::getPool()->destroyComponent(this->id);
	ComponentPoolLocator<Rendering>::getPool()->destroyComponent(this->id);
	ComponentPoolLocator<Motion>::getPool()->destroyComponent(this->id);
	ComponentPoolLocator<Physics>::getPool()->destroyComponent(this->id);

	// TODO - Use ScriptSystem to iterate over all Script ComponentPools and
	// call pool->destroyComponent(this->id).
	//ComponentPoolLocator<Script>::getPool()->destroyComponent(this->id);

}
