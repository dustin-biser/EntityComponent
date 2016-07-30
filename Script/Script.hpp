//
// Script.hpp
//
#pragma once

#include "Core/Component.hpp"

// Forward declare.
class ScriptBehavior;


// To be derived by subclasses to provide custom behavior for GameObjects.
class Script : public Component {
public:
	Script (
		EntityID id,
		GameObject & gameObject
	);

	virtual ~Script();

	virtual void onUpdate();

	virtual void onCollision();


	// Define more callback methods here ...


private:
	friend class GameObject;

	Script * scriptBehavior;
};
