//
// GameObject.cpp
//
#include "GameObject.hpp"
#include "InputComponent.hpp"
#include "MotionComponent.hpp"
#include "GraphicsComponent.hpp"
#include "PhysicsComponent.hpp"

//---------------------------------------------------------------------------------------
// Constructor
// Sets default components.
GameObject::GameObject () 
	: input(new InputComponent()),
	  motion(new MotionComponent()),
	  graphics(new GraphicsComponent()),
	  physics(new PhysicsComponent())
{

}

//---------------------------------------------------------------------------------------
GameObject::~GameObject()
{
	delete input;
	delete motion;
	delete graphics;
	delete physics;
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
