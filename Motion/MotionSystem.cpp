//
// MotionSystem.cpp
//
#if false

#include "MotionSystem.hpp"
#include "ComponentPool.hpp"
#include "GameObject.hpp"
#include "Motion.hpp"

#include "time.h"

class MotionSystemImpl {
private:
	friend class MotionSystem;

	void update (
		ComponentPool * gameObjectPool,
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
	ComponentPool * gameObjectPool,
	float ellapsedTimeInSeconds
) {
	impl->update(gameObjectPool, ellapsedTimeInSeconds);
}

//---------------------------------------------------------------------------------------
void MotionSystemImpl::update (
	ComponentPool * gameObjectPool,
	float ellapsedTimeInSeconds
) {
	// Update motion for each gameObject
	GameObject * gameObject = gameObjectPool->beginActive();
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
