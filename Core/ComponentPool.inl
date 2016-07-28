//
// ComponentPool.inl
//

#ifndef _COMPONENT_POOL_INL_
#define _COMPONENT_POOL_INL_

#include "ComponentPool.hpp"

#include <unordered_map>
using std::unordered_map;

#include "Config/EngineSettings.hpp"



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


	T * pool;
	const size_t m_numPoolElements = MAX_COMPONENTS_PER_TYPE;

	// Address of first available object for allocation.
	T * m_firstAvailable;

	// Address of lasst available object for allocation.
	T * m_lastAvailable;

	// Up-to-date mapping from EntityID to memory address of Component object.
	std::unordered_map<EntityID::id_type, T *> m_idToComponentMap;
};


//---------------------------------------------------------------------------------------
// Constructor
template <class T>
ComponentPoolImpl<T>::ComponentPoolImpl()
{
	// Allocate enough bytes to hold m_numPoolElements of T objects.
	T * pool = reinterpret_cast<T *>(new char[sizeof(T) * m_numPoolElements]);

	m_firstAvailable = pool;

	// Create FreeList, so that each T object points to next T object in pool.
	FreeList<T> * freeList;
	size_t lastPoolIndex = m_numPoolElements - 1;
	for (size_t i(0); i < lastPoolIndex; ++i) {
		freeList = reinterpret_cast<FreeList<T> *>(&pool[i]);
		freeList->next = &pool[i + 1];
	}
	// Last T object points to nullptr.
	freeList = reinterpret_cast<FreeList<T> *>(&pool[lastPoolIndex]);
	freeList->next = nullptr;

	m_lastAvailable = &pool[lastPoolIndex];
}


//---------------------------------------------------------------------------------------
// Destructor
template <class T>
ComponentPoolImpl<T>::~ComponentPoolImpl()
{
	// Free pool resources.
	// Calls destructor on all T objects.
	delete[] pool;
}

//---------------------------------------------------------------------------------------
// Constructor
template <class T>
ComponentPool<T>::ComponentPool () 
{
	// Compile-time check
	static_assert(std::is_base_of<Component, T>::value,
		"T must be a type derived from class Component");

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
		return size_t(m_firstAvailable - &pool[0]);
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

	T * pObject = m_idToComponentMap.at(id);

	// Call destructor T
	pObject->~T();

	// Remove unused id
	m_idToComponentMap.erase(id);

	// Swap pObject with last active in order to keep all
	// active objects in front of pool.
	T * pLastActive = &pool[numActive - 1];
	if (pLastActive != pObject) {
		// Update idPointerMap to moved destination
		m_idToComponentMap[pLastActive->id] = pObject;

		std::swap(*pObject, *pLastActive);

		// Point to new location
		pObject = pLastActive;
	}

	// Set obj.next = firstAvailable.next
	reinterpret_cast<FreeList *>(pObject)->next = m_firstAvailable;

	// obj is now the firstAvailable.
	m_firstAvailable = pObject;
}

//---------------------------------------------------------------------------------------
template <class T>
T * ComponentPool<T>::createComponent (
	EntityID id,
	GameObject & gameObject
) {
	T * location = impl->createComponent(id);

	// Place object at location and call constructor.
	T * newObject = new (location) T(id, gameObject);

	return newObject;
}

//---------------------------------------------------------------------------------------
template <class T>
void ComponentPool<T>::destroyComponent(
	EntityID id
) {
	impl->destroy(id);
}

//---------------------------------------------------------------------------------------
template <class T>
T * ComponentPool<T>::getComponent (
	EntityID id
) {
	return impl->m_idToComponentMap.at(id);
}

//---------------------------------------------------------------------------------------
template <class T>
T * ComponentPool<T>::beginActive() const
{
	return impl->pool;
}

//---------------------------------------------------------------------------------------
template <class T>
size_t ComponentPool<T>::numActive() const
{
	return impl->numActiveObjects();
}


#endif //_COMPONENT_POOL_INL_
