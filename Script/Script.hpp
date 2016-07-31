//
// Script.hpp
//
#pragma once

#include "Core/Component.hpp"


// To be derived by subclasses to provide custom behavior for GameObjects.
class Script : public Component {
public:
	Script();

	Script (
		EntityID id,
		GameObject & gameObject
	);

	virtual ~Script();

	virtual void init();

	virtual void update();

	virtual void onCollision();


	// Define more callback methods here ...


private:
	friend class GameObject;
	friend class ScriptSystem;

	Script * m_script;
};


// All includes a Script may need.
#include "Assets/MeshDirectory.hpp"

#include "Core/GameConstants.hpp"
#include "Core/GameObject.hpp"
#include "Core/Input.hpp"
#include "Core/Transform.hpp"
#include "Core/Screen.hpp"

#include "Motion/Motion.hpp"
#include "Physics/Physics.hpp"
#include "Rendering/Rendering.hpp"

