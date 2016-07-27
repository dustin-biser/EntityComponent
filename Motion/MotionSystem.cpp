//
// MotionSystem.cpp
//
#if false

#include "MotionSystem.hpp"
#include "GameObjectPool.hpp"
#include "GameObject.hpp"
#include "MotionComponent.hpp"

#include "time.h"

class MotionSystemImpl {
private:
	friend class MotionSystem;

	void update (
		GameObjectPool * gameObjectPool,
		float ellapsedTimeInSeconds
	);
};

//---------------------------------------------------------------------------------------
MotionSystem::MotionSystem()
{
	impl = new MotionSystemImpl();
}

//---------------------------------------------------------------------------------------
MotionSystem::~MotionSystem()
{
	delete impl;
	impl = nullptr;
}

//---------------------------------------------------------------------------------------
void MotionSystem::update (
	GameObjectPool * gameObjectPool,
	float ellapsedTimeInSeconds
) {
	impl->update(gameObjectPool, ellapsedTimeInSeconds);
}

//---------------------------------------------------------------------------------------
void MotionSystemImpl::update (
	GameObjectPool * gameObjectPool,
	float ellapsedTimeInSeconds
) {
	// Update motion for each gameObject
	GameObject * gameObject = gameObjectPool->begin();
	for (size_t i(0); i < gameObjectPool->numActive(); ++i) {
		gameObject[i].motion->update(&gameObject[i], ellapsedTimeInSeconds);

		// Update motion for each child of gameObject
		for (auto & child : gameObject[i].childObjects) {
			GameObject * childGameObject = child.residentPool->getObject(child.id);
			childGameObject->motion->update(childGameObject, ellapsedTimeInSeconds);
		}
	}
}

#endif
