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
	: Entity(EntityID::generateID(), other.m_name) // Generate a new EntityID
{
	const EntityID otherID = other.m_id;

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

	ComponentPoolBase * scriptPool = ScriptSystem::getScriptPoolForEntity(otherID);
	if (scriptPool) {
		scriptPool->allocateComponent(*this);
		ScriptSystem::addScriptPool(m_id, scriptPool);
	}

}

//---------------------------------------------------------------------------------------
void GameObject::setActive (
	bool activeStatus
) {
	// Notify ComponentPools to set active status for Components associated with EnityID:
	ComponentPoolLocator<Transform>::getPool()->setActive(m_id, activeStatus);
	ComponentPoolLocator<Rendering>::getPool()->setActive(m_id , activeStatus);
	ComponentPoolLocator<Motion>::getPool()->setActive(m_id, activeStatus);
	ComponentPoolLocator<Physics>::getPool()->setActive(m_id, activeStatus);

	// Set associated Script's status.
	ScriptSystem::setActive(m_id, activeStatus);
}

//---------------------------------------------------------------------------------------
void GameObject::setParent (
	const GameObject & other
) {
	this->transform().setParent(other.transform());
}

//---------------------------------------------------------------------------------------
Transform & GameObject::transform () const
{
	return *ComponentPoolLocator<Transform>::getPool()->getComponent(m_id);
}

//---------------------------------------------------------------------------------------
void GameObject::destroy()
{
	removeComponent<Transform>();
	removeComponent<Rendering>();
	removeComponent<Motion>();
	removeComponent<Physics>();

	// If GameObject has an associated Script, destroy it.
	ComponentPoolBase * scriptPool = ScriptSystem::getScriptPoolForEntity(m_id);
	if (scriptPool) {
		scriptPool->destroyComponent(m_id);
	}
}
