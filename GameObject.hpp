//
// GameObject.hpp
//
#pragma once

#include <vector>
#include "TransformComponent.hpp"
#include "EntityID.hpp"

// Forward declare
class InputComponent;
class MotionComponent;
class GraphicsComponent;
class PhysicsComponent;


class GameObject {
public:
	GameObject();

	EntityID id;
	TransformComponent transform;

// Optional Components
	InputComponent * input;
	MotionComponent * motion;
	GraphicsComponent * graphics;
	PhysicsComponent * physics;

	std::vector<GameObject *> childObjects;
};
