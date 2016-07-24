//
// GameObject.hpp
//
#pragma once

#include <vector>
#include "TransformComponent.hpp"

// Forward declare
class InputComponent;
class MotionComponent;
class GraphicsComponent;
class PhysicsComponent;


typedef unsigned long GameObjectID;


class GameObject {
public:
	GameObject();

	GameObjectID id;
	TransformComponent transform;

	InputComponent * input;
	MotionComponent * motion;
	GraphicsComponent * graphics;
	PhysicsComponent * physics;

	std::vector<GameObject *> childObjects;


	static GameObjectID generateID();

private:
	static GameObjectID nextID;

};
