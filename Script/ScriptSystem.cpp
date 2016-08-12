//
// ScriptSystem.cpp
//
#include "ScriptSystem.hpp"

#include "Core/ComponentPool.hpp"

#include "Script/Script.hpp"


// Initialize m_scriptPools
std::vector<ComponentPoolBase *> ScriptSystem::m_scriptPools;


//---------------------------------------------------------------------------------------
void ScriptSystem::init()
{
	for (auto scriptPool : m_scriptPools) {
		Script * script = static_cast<const ComponentPool<Script> *>(scriptPool)->beginActive();
		for (size_t i(0); i < scriptPool->numActive(); ++i) {
			script[i].init();
		}
	}
}

//---------------------------------------------------------------------------------------
void ScriptSystem::update()
{
	for (auto scriptPool : m_scriptPools) {
		Script * script = static_cast<const ComponentPool<Script> *>(scriptPool)->beginActive();
		for (size_t i(0); i < scriptPool->numActive(); ++i) {
			script[i].update();
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
