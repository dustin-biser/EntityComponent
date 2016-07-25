//
// ProjectileCollisionObsever.cpp
//
#include "ProjectileCollisionObserver.hpp"

#include "GameObject.hpp"
#include "GameObjectPool.hpp"

void ProjectileCollisionObserver::onNotify (
	GameObject * gameObject, 
	PhysicsEvent * physicsEvent
) {
	//if (physcisEvent->id == PHYSICS_EVENT_COLLISION) {
	//	gameObject->destroy();
	//}
}
