//
// ScriptSystem.cpp
//

#include "ScriptSystem.hpp"

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"

#include "Script/Script.hpp"


// Initialize scriptPool.
ComponentPool<Script> * ScriptSystem::m_scriptPool = ComponentPoolLocator<Script>::getPool();


//---------------------------------------------------------------------------------------
void ScriptSystem::init()
{
	Script * script = m_scriptPool->beginActive();
	for (size_t i(0); i < m_scriptPool->numActive(); ++i) {
		script->m_script->init();
	}
}

//---------------------------------------------------------------------------------------
void ScriptSystem::update()
{
	Script * script = m_scriptPool->beginActive();
	for (size_t i(0); i < m_scriptPool->numActive(); ++i) {
		script->m_script->update();
	}
}


