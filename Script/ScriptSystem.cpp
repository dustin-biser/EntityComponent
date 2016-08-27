//
// ScriptSystem.cpp
//
#include "ScriptSystem.hpp"

#include "Core/ComponentPool.hpp"

#include "Script/Script.hpp"


// Initialize m_scriptPools
std::vector<ComponentPoolBase *> ScriptSystem::m_scriptPools;

typedef char byte;

//---------------------------------------------------------------------------------------
void ScriptSystem::init()
{
	Script * script;
	for (auto scriptPool : m_scriptPools) {
		for (size_t i(0); i < scriptPool->numActive(); ++i) {
			script = reinterpret_cast<Script *>((*scriptPool)[i]);
			script->init();
		}
	}
}

//---------------------------------------------------------------------------------------
void ScriptSystem::update()
{
	Script * script;
	for (auto scriptPool : m_scriptPools) {
		for (size_t i(0); i < scriptPool->numActive(); ++i) {
			script = reinterpret_cast<Script *>((*scriptPool)[i]);
			script->update();
		}
	}
}

//---------------------------------------------------------------------------------------
void ScriptSystem::addScriptPool (
	const ComponentPoolBase * scriptPool
) {
	// Check if componentPool of Scripts already exists
	for (auto currentScriptPool : m_scriptPools) {
		if (currentScriptPool == scriptPool) {
			return;
		}
	}
	// Pool does not yet exist, so insert it.
	m_scriptPools.push_back(const_cast<ComponentPoolBase *>(scriptPool));
}

//---------------------------------------------------------------------------------------
ComponentPoolBase ** ScriptSystem::getScriptPoolsBegin()
{
	return m_scriptPools.data();
}

//---------------------------------------------------------------------------------------
size_t ScriptSystem::numScriptPools()
{
	return m_scriptPools.size();
}
