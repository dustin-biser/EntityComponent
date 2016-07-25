//
// ProjectileCollisionObsever.hpp
//

#include "PhysicsEventObserver.hpp"

// Forward declare.
class GameObject;
class PhysicsEvent;

class ProjectileCollisionObserver : public PhysicsEventObserver {
public:

	void onNotify (
		GameObject * gameObject,
		PhysicsEvent * physicsEvent
	) override;

};