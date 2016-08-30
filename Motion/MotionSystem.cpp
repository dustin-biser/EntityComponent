//
// MotionSystem.cpp
//
#include "MotionSystem.hpp"

#include "ComponentPoolLocator.hpp"
#include "ComponentPool.hpp"
#include "Motion.hpp"



//---------------------------------------------------------------------------------------
/*static*/ 
void MotionSystem::update (
	float ellapsedTimeInSeconds
) {
	ComponentPool<Motion> * motionPool = ComponentPoolLocator<Motion>::getPool();
	Motion * motionList = motionPool->beginActive();
	for (size_t i(0); i < motionPool->numActive(); ++i) {
		Motion & motion = motionList[i];
		Transform & transform = motion.transform();
		transform.position += motion.velocity * vec2(ellapsedTimeInSeconds);
	}
}

