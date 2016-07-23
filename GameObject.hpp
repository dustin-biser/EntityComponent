//
// GameObject.hpp
//
#pragma once

#include <vector>
#include "vec2.hpp"

// Forward declare
class InputComponent;
class MotionComponent;
class GraphicsComponent;
class PhysicsComponent;


class GameObject {
public:
	GameObject();

	struct TransformComponent {
		vec2 position;
		vec2 scale;
		float rotationAngle;
	} transform;

// Optional Components
	InputComponent * input;
	MotionComponent * motion;
	GraphicsComponent * graphics;
	PhysicsComponent * physics;

	std::vector<GameObject *> childObjects;
};
