//
// Script.hpp
//
#pragma once

#include "Core/Component.hpp"

#include <type_traits>

// Forward declare.
class GameObject;


// Base class for all custom Scripts. 
// Script components add behavior to GameObjects.
class Script : public Component {
public:
	Script();

	Script (
		const GameObject & gameObject
	);

	template <class T>
	static
	typename std::enable_if<std::is_base_of<Script, T>::value,
	T &>::type replicate(const T & other);

	virtual ~Script();

	virtual void init() {};

	virtual void update() {};

	virtual void onCollision() {};


	// Define more callback methods here ...

};


#include "Script.inl"



// All includes a derived Script class may need.
#include "Assets/MeshDirectory.hpp"

#include "Core/Entity.hpp"
#include "Core/GameConstants.hpp"
#include "Core/GameObject.hpp"
#include "Core/Input.hpp"
#include "Core/Transform.hpp"
#include "Core/Screen.hpp"

#include "Motion/Motion.hpp"
#include "Physics/Physics.hpp"
#include "Rendering/Rendering.hpp"

