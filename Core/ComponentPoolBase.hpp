//
// ComponentPoolBase.hpp
//
#pragma once


// Forward declare.
class GameObject;
class EntityID;
class Component;


// Abstract base class for ComponentPools.
class ComponentPoolBase {
public:
	virtual ~ComponentPoolBase() { };

	virtual void allocateComponent (
		const GameObject & gameObject
	) = 0;

	virtual void destroyComponent (
		const EntityID & id
	) = 0;

	virtual void setActive (
		const EntityID & id,
		bool activeStatus
	) = 0;

	virtual bool hasComponent (
		const EntityID & id
	) const = 0;

	// Returns the number of objects in active list.
	virtual size_t numActive() const = 0;

	// Returns a reference to the Component at index within Pool.
	// Assumtes 0 <= index < numActive().
	virtual Component * operator [] (int index) const = 0;

};