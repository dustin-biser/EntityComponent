//
// GameObject.cpp
//
#include "GameObject.hpp"
#include "GameObjectPool.hpp"
#include "MotionComponent.hpp"
#include "GraphicsComponent.hpp"
#include "PhysicsComponent.hpp"

//---------------------------------------------------------------------------------------
// Constructor
// Sets default components.
GameObject::GameObject () 
	: motion(new MotionComponent()),
	  graphics(new GraphicsComponent()),
	  physics(new PhysicsComponent())
{

}

//---------------------------------------------------------------------------------------
GameObject::~GameObject()
{
	// Delete components
	{
		delete motion; motion = nullptr;
		delete graphics; graphics = nullptr;
		delete physics; physics = nullptr;
	}

	// Delete children GameObjects
	for (auto & child : childObjects) {
		GameObjectPool * childPool = child.residentPool;
		childPool->destroy(child.id);
	}
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

//---------------------------------------------------------------------------------------
void GameObject::addChild (
	GameObject * child
) {
	GameObjectID child_id = child->id;
	if (child_id == this->id) {
		// Attempting to add self as a child!
		throw;
	}
	ChildGameObject childObj {child_id, child->residentPool};
	childObjects.push_back(childObj);
}

//---------------------------------------------------------------------------------------
GameObject * GameObject::getChild (
	GameObjectID childID
) const {
	for (auto & child : childObjects) {
		if (childID == child.id) {
			return child.residentPool->getObject(childID);
		}
	}

	// Not found.
	return nullptr;
}

//---------------------------------------------------------------------------------------
GameObjectPool * GameObject::getPool() const
{
	return this->residentPool;
}
