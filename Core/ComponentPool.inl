//
// ComponentPool.inl
//
#ifndef _COMPONENT_POOL_INL_
#define _COMPONENT_POOL_INL_

#include "ComponentPool.hpp"

#include <cstring>
using std::memmove;
#include <unordered_map>
using std::unordered_map;

#include "Config/EngineSettings.hpp"

#include "Core/EntityID.hpp"
#include "Core/Component.hpp"
#include "Core/GameObject.hpp"
#include "Core/Utils.hpp"


template <class T>
class ComponentPoolImpl {
private:
	friend class ComponentPool<T>;

// Methods:
	ComponentPoolImpl();
	~ComponentPoolImpl();

	size_t numActiveObjects() const;

	T * createComponent (
		const EntityID & id
	);

	void destroyComponent (
		const EntityID & id
	);

	void activateComponent (
		const EntityID & id
	);

	void deactivateComponent (
		const EntityID & id
	);

	bool isActive (
		const EntityID & id
	);

	void moveObjects (
		T * dest,
		T * source,
		size_t numObjects
	);

	Component * operator [] (int index) const;


// Members:
	T * m_pool;
	const size_t m_numPoolElements = EngineSettings::MAX_COMPONENTS_PER_TYPE;

	// Address of first available object for allocation.
	T * m_firstAvailable;

	// Address of last available object for allocation.
	T * m_lastAvailable;

	// Up-to-date mapping from EntityID to memory address of Component object within pool.
	// Allows for O(1) retrieval.
	std::unordered_map<EntityID::id_type, T *> m_idToComponentMap;

	// Deactivated components are listed here.
	// Allows for O(1) retrieval.
	std::unordered_map<EntityID::id_type, bool> m_idToActiveStatusMap;

	static constexpr size_t sizeOfComponent = sizeof(T);
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
	T * freeList;
	size_t lastPoolIndex = m_numPoolElements - 1;
	for (size_t i(0); i < lastPoolIndex; ++i) {
		freeList = &m_pool[i];
		freeList->next = &m_pool[i + 1];
	}
	// Last T object points to nullptr.
	m_lastAvailable = &m_pool[lastPoolIndex];
	m_lastAvailable->next = nullptr;
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
	const EntityID & id
) {
	if (m_firstAvailable == nullptr) {
		// No space left in pool for allocation.
		throw;
	}

	T * result = m_firstAvailable;
	m_firstAvailable = reinterpret_cast<T *>(m_firstAvailable->next);

	// Update pointer map
	m_idToComponentMap[id.value] = result;

	// Update active status
	m_idToActiveStatusMap[id.value] = true;

	return result;
}

//---------------------------------------------------------------------------------------
template <class T>
void ComponentPoolImpl<T>::destroyComponent (
	const EntityID & id
) {
	if (m_idToComponentMap.count(id.value) < 1) {
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
	T * pLastActive = &m_pool[numActiveObjects() - 1];
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
	pObject->next = m_firstAvailable;

	// pObject is now the firstAvailable.
	m_firstAvailable = pObject;
}

//---------------------------------------------------------------------------------------
template <class T>
T & ComponentPool<T>::createComponent (
	const GameObject & gameObject
) {
	EntityID id = gameObject.getEntityID();
	if (impl->m_idToComponentMap.count(id.value) > 0) {
		// Component already exists, so return it.
		return *impl->m_idToComponentMap.at(id.value);
	}

	T * location = impl->createComponent(id);

	// Place Component at location.
	T * newComponent(new (location) T());
	// Initialize Component's EntityID and GameObject.
	newComponent->id = id;
	newComponent->name = gameObject.getName();
	newComponent->m_gameObject = const_cast<GameObject *>(&gameObject);

	return *newComponent;
}

//---------------------------------------------------------------------------------------
template <class T>
void ComponentPool<T>::allocateComponent (
	const GameObject & gameObject
) {
	this->createComponent(gameObject);
}

//---------------------------------------------------------------------------------------
template <class T>
void ComponentPool<T>::destroyComponent (
	const EntityID & id
) {
	impl->destroyComponent(id);
}

//---------------------------------------------------------------------------------------
template <class T>
T * ComponentPool<T>::getComponent (
	const EntityID & id
) const
{
	if (impl->m_idToComponentMap.count(id.value) > 0) {
		return impl->m_idToComponentMap.at(id.value);
	}
	else {
		return nullptr;
	}
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

//---------------------------------------------------------------------------------------
template <class T>
bool ComponentPoolImpl<T>::isActive (
	const EntityID & id
) {
	return m_idToActiveStatusMap.at(id.value);
}


//---------------------------------------------------------------------------------------
template <class T>
void ComponentPool<T>::setComponentActive (
	const EntityID & id,
	bool activate
) {
	if (impl->m_idToComponentMap.count(id.value) > 0) {
		// Component with EntityID exists.

		if ((activate) && !impl->isActive(id)) {
			impl->activateComponent(id);
		}
		else if ((!activate) && impl->isActive(id)) {
			impl->deactivateComponent(id);
		}
	}
}

//---------------------------------------------------------------------------------------
template <class T>
void ComponentPoolImpl<T>::moveObjects (
	T * dest,
	T * source,
	size_t numObjects
) {
	memmove(dest, source, sizeof(T) * numObjects);

	// For each object moved, update its pointer map location.
	T * pMovedObject = dest;
	for (size_t i(0); i < numObjects; ++i) {
		m_idToComponentMap.at(pMovedObject->getEntityID().value) = pMovedObject;
		++pMovedObject;
	}
}

//---------------------------------------------------------------------------------------
template <class T>
void ComponentPoolImpl<T>::deactivateComponent (
	const EntityID & id
) {
	// Locate object from id.
	T * pObject = m_idToComponentMap.at(id.value);

	// Place object at m_lastAvailable location.
	std::memmove(m_lastAvailable, pObject, sizeof(T));

	// Update pointer map
	m_idToComponentMap.at(id.value) = m_lastAvailable;

	// Update active status
	m_idToActiveStatusMap.at(id.value) = false;

	// Move all Active Components following pObject forward one spot
	// toward front of pool.
	size_t numObjectsToMove = static_cast<size_t>(m_firstAvailable - pObject - 1);
	this->moveObjects(pObject, pObject + 1, numObjectsToMove);

	// Update last available object on free list
	--m_lastAvailable;

	// Update first available object on free list
	--m_firstAvailable;

	if (m_lastAvailable != m_firstAvailable) {
		m_firstAvailable->next = m_firstAvailable + 1;
	}
	else {
		m_firstAvailable->next = nullptr;
	}
}

//---------------------------------------------------------------------------------------
template <class T>
void ComponentPoolImpl<T>::activateComponent (
	const EntityID & id
) {
	// Locate object from id.
	T * pObject = m_idToComponentMap.at(id.value);

	// Place object at m_firstAvailable location.
	std::memmove(m_firstAvailable, pObject, sizeof(T));

	// Update pointer map
	m_idToComponentMap.at(id.value) = m_firstAvailable;

	// Update active status
	m_idToActiveStatusMap.at(id.value) = true;

	// Move all Inactive Components in front of pObject backward one spot toward
	// end of pool.
	size_t numObjectsToMove = pObject - m_lastAvailable - 1;
	this->moveObjects(pObject, m_lastAvailable + 1, numObjectsToMove);

	++m_firstAvailable;
	++m_lastAvailable;
	if (m_firstAvailable != m_lastAvailable) {
		m_firstAvailable->next = m_firstAvailable + 1;
	}
}

//---------------------------------------------------------------------------------------
template <class T>
bool ComponentPool<T>::hasComponent (
	const EntityID & id
) const {
	return getComponent(id) == nullptr;
}

//---------------------------------------------------------------------------------------
template <class T>
Component * ComponentPool<T>::operator [] (
	int index
) const {
	return impl->operator[](index);
}

//---------------------------------------------------------------------------------------
template <class T>
Component * ComponentPoolImpl<T>::operator [] (
	int index
) const {
	ASSERT(index > -1);
	ASSERT(index < static_cast<int>(numActiveObjects()));

	// The caller could be a pointer to ComponentPool<T>, yet the underlying
	// Components in pool are derived from T.  Pointer arithmetic such as m_pool + num 
	// would increment pointer by incorrect amount of bytes if derived Component is
	// larger than base class Component.
	
	char * pByteOffset = reinterpret_cast<char *>(m_pool) + (index * sizeOfComponent);
	return reinterpret_cast<Component *>(pByteOffset);
}


#endif //_COMPONENT_POOL_INL_
