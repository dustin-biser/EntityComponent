//
// ScriptSystem.cpp
//
#include "ScriptSystem.hpp"

#include "Core/ComponentPool.hpp"

#include "Script/Script.hpp"



// Store list of Script ComponentPools
static std::vector<ComponentPoolBase *> m_scriptPools;

typedef size_t ScriptPoolIndex;
// Hash map to retrieve ScriptPoolIndex from EntityID in constant time.
// ScriptPoolIndex corresponds to an index within m_scriptPools.
static std::unordered_map<EntityID::id_type, ScriptPoolIndex> m_idToScriptPoolIndexMap;


//---------------------------------------------------------------------------------------
void ScriptSystem::update()
{
	// During a call to Script::update(), another Script could be created incrementing the
	// size of m_scriptPools and thus invalidating its iterator.  Therefore range-based
	// for loops wont work here.
	Script * script(nullptr);
	for (size_t poolIndex(0); poolIndex < m_scriptPools.size(); ++poolIndex) {
		ComponentPoolBase * scriptPool = m_scriptPools[poolIndex];
		for (size_t i(0); i < scriptPool->numActive(); ++i) {
			script = reinterpret_cast<Script *>((*scriptPool)[i]);
			script->update();
		}
	}
}

//---------------------------------------------------------------------------------------
void ScriptSystem::addScriptPool (
	const EntityID & id,
	const ComponentPoolBase * scriptPool
) {
	// Check if componentPool of Scripts already exists
	//for (auto currentScriptPool : m_scriptPools) {
	int poolIndex(0);
	const int numPools = m_scriptPools.size();
	for(; poolIndex < numPools; ++poolIndex) {
		if (m_scriptPools[poolIndex] == scriptPool) {
			break;
		}
	}

	if (poolIndex == numPools) {
		// ComponentPool is not in the list, so insert it.
		m_scriptPools.push_back(const_cast<ComponentPoolBase *>(scriptPool));
	}

	// Update hash map
	m_idToScriptPoolIndexMap[id.value] = poolIndex;
}

//---------------------------------------------------------------------------------------
ComponentPoolBase * ScriptSystem::getScriptPoolForEntity(const EntityID & id)
{
	if (m_idToScriptPoolIndexMap.count(id.value) > 0) {
		size_t poolIndex = m_idToScriptPoolIndexMap.at(id.value);
		return m_scriptPools[poolIndex];
	}
	else {
		return nullptr;
	}
}

//---------------------------------------------------------------------------------------
size_t ScriptSystem::numScriptPools()
{
	return m_scriptPools.size();
}

//---------------------------------------------------------------------------------------
void ScriptSystem::setActive (
	const EntityID & id,
	bool activeStatus
) {
	ScriptPoolIndex poolIndex = m_idToScriptPoolIndexMap[id.value];
	m_scriptPools[poolIndex]->setActive(id, activeStatus);
}
