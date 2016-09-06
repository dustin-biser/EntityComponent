//
// ScriptSystem.hpp
//
#pragma once

#include <vector>

// Forward declare.
class ComponentPoolBase;
class EntityID;


class ScriptSystem {
public:

	// Calls Script::update() on all active Script Components.
	static void update();

	static void addScriptPool (
		const EntityID & id,
		const ComponentPoolBase * scriptPool
	);

	// Returns a pointer to ComponentPool containing Script with associated 
	// EntityID.  Returns nullptr if no Script exists for EntityID.
	static ComponentPoolBase * getScriptPoolForEntity (
		const EntityID & id
	);
	
	static size_t numScriptPools();

	static void setActive (
		const EntityID & id,
		bool activeStatus
	);

};
