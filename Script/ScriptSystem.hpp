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

	// Calls Script::init() on all active Script Components.
	static void init();

	// Calls Script::update() on all active Script Components.
	static void update();

	static void addScriptPool(const ComponentPoolBase * scriptPool);

	static ComponentPoolBase ** getScriptPoolsBegin();
	
	static size_t numScriptPools();


private:
	static std::vector<ComponentPoolBase *> m_scriptPools;
};
