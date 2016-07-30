//
// ComponentPool.inl
//

#ifndef _COMPONENT_POOL_INL_
#define _COMPONENT_POOL_INL_

#include "ComponentPool.hpp"

#include <unordered_map>
using std::unordered_map;

#include "Config/EngineSettings.hpp"

#include "Core/Component.hpp"



template <class T>
struct FreeList {
	T * next;
};


template <class T>
class ComponentPoolImpl {
private:
	friend class ComponentPool<T>;

	ComponentPoolImpl();
	~ComponentPoolImpl();

	size_t numActiveObjects() const;

	T * createComponent (
		EntityID id
	);

	void destroyComponent (
		EntityID id
	);


	T * m_pool;
	const size_t m_numPoolElements = EngineSettings::MAX_COMPONENTS_PER_TYPE;

	// Address of first available object for allocation.
	T * m_firstAvailable;

	// Address of last available object for allocation.
	T * m_lastAvailable;

	// Up-to-date mapping from EntityID to memory address of Component object within pool.
	// Allows O(1) for retrieval.
	std::unordered_map<EntityID::id_type, T *> m_idToComponentMap;
};


//---------------------------------------------------------------------------------------
// Constructor
template <class T>
ComponentPoolImpl<T>::ComponentPoolImpl()
{
	// Allocate enough bytes to hold m_numPoolElements of T objects.
	m_pool = reinterpret_cast<T *>(new char[sizeof(T) * m_numPoolElements]);

	m_firstAvailable = m_pool;

	// Create FreeList, so that each T object points to next T object in pool.
	FreeList<T> * freeList;
	size_t lastPoolIndex = m_numPoolElements - 1;
	for (size_t i(0); i < lastPoolIndex; ++i) {
		freeList = reinterpret_cast<FreeList<T> *>(&m_pool[i]);
		freeList->next = &m_pool[i + 1];
	}
	// Last T object points to nullptr.
	freeList = reinterpret_cast<FreeList<T> *>(&m_pool[lastPoolIndex]);
	freeList->next = nullptr;

	m_lastAvailable = &m_pool[lastPoolIndex];
}


//---------------------------------------------------------------------------------------
// Destructor
template <class T>
ComponentPoolImpl<T>::~ComponentPoolImpl()
{
	// Free pool resources.
	// Calls destructor on all T objects.
	delete[] m_pool;
}

//---------------------------------------------------------------------------------------
// Constructor
template <class T>
ComponentPool<T>::ComponentPool () 
{
	assertIsDerivedFromComponent<T> ();

	impl = new ComponentPoolImpl<T>();
}

//---------------------------------------------------------------------------------------
// Destructor
template <class T>
ComponentPool<T>::~ComponentPool()
{
	delete impl;
}


//---------------------------------------------------------------------------------------
template <class T>
size_t ComponentPoolImpl<T>::numActiveObjects() const
{
	if (m_firstAvailable == nullptr) {
		return m_numPoolElements;
	}
	else {
		return size_t(m_firstAvailable - &m_pool[0]);
	}
}


//---------------------------------------------------------------------------------------
template <class T>
T * ComponentPoolImpl<T>::createComponent (
	EntityID id
) {
	if (m_firstAvailable == nullptr) {
		// No space left in pool for allocation.
		throw;
	}

	T * result = m_firstAvailable;
	m_firstAvailable = reinterpret_cast<FreeList<T> *>(m_firstAvailable)->next;

	// Update idPointerMap
	m_idToComponentMap[id.value] = result;

	return result;
}

//---------------------------------------------------------------------------------------
template <class T>
void ComponentPoolImpl<T>::destroyComponent (
	EntityID id
) {
	size_t numActive = numActiveObjects();
	if (numActive == 0) {
		// No objects left to destroy.
		throw;
	}
	else if (m_idToComponentMap.count(id.value) < 1) {
		// No Component in this pool with EntityID.
		return;
	}

	T * pObject = m_idToComponentMap.at(id.value);

	// Call destructor for T
	pObject->~T();

	// Remove unused id in map.
	m_idToComponentMap.erase(id.value);

	// Swap pObject with last active in order to keep all
	// active objects in front of pool.
	T * pLastActive = &m_pool[numActive - 1];
	if (pLastActive != pObject) {
		// Register new address for EntityID
		m_idToComponentMap[pLastActive->getEntityID().value] = pObject;

		std::swap(*pObject, *pLastActive);
		
		// Point to new location
		pObject = pLastActive;

		// TODO - Need to check child status, and move parent + children together.
		// For Transform Components only.
	}

	// Make pObject.next point to first available object on FreeList.
	reinterpret_cast<FreeList<T> *>(pObject)->next = m_firstAvailable;

	// pObject is now the firstAvailable.
	m_firstAvailable = pObject;
}

//---------------------------------------------------------------------------------------
template <class T>
T * ComponentPool<T>::createComponent (
	EntityID id,
	GameObject & gameObject
) {
	if (impl->m_idToComponentMap.count(id.value) > 0) {
		// Component already exists, so return it.
		return impl->m_idToComponentMap.at(id.value);
	}

	T * location = impl->createComponent(id);

	// Place object at location and call constructor.
	T * newObject(new (location) T(id, gameObject));

	return newObject;
}

//---------------------------------------------------------------------------------------
template <class T>
void ComponentPool<T>::destroyComponent (
	EntityID id
) {
	impl->destroyComponent(id);
}

//---------------------------------------------------------------------------------------
template <class T>
T * ComponentPool<T>::getComponent (
	EntityID id
) {
	return impl->m_idToComponentMap.at(id.value);
}

//---------------------------------------------------------------------------------------
template <class T>
T * ComponentPool<T>::beginActive() const
{
	return impl->m_pool;
}

//---------------------------------------------------------------------------------------
template <class T>
size_t ComponentPool<T>::numActive() const
{
	return impl->numActiveObjects();
}


#endif //_COMPONENT_POOL_INL_
