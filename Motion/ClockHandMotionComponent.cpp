//
// ClockHandMotionComponent.cpp
//

#if false

#include "ClockHandMotionComponent.hpp"
#include "GameObject.hpp"
#include "Rendering.hpp"
#include "Mesh2d.hpp"
#include "GameConstants.hpp"

#include "time.h"


//---------------------------------------------------------------------------------------
Motion * ClockHandMotionComponent::clone() const
{
	return new ClockHandMotionComponent(*this);
}

//---------------------------------------------------------------------------------------
void ClockHandMotionComponent::update (
	GameObject * gameObject,
	float elapsedTime
) {

	MeshID meshId = gameObject->graphics->mesh->meshId;

	int hour, minute, second;
	GetTime(hour, minute, second);

	float rotationAngle;
	const float twoPI = 2.0f * k_PI;

	if (meshId.compare("HourHand") == 0) {
		rotationAngle = -1.0f * (hour / 12.0f) * twoPI;
	}
	else if (meshId.compare("MinuteHand") == 0) {
		rotationAngle = -1.0f * (minute / 60.0f) * twoPI;
	}
	else if (meshId.compare("SecondHand") == 0) {
		rotationAngle = -1.0f * (second / 60.0f) * twoPI;
	}

	gameObject->transform.rotationAngle = rotationAngle;
}

#endif
