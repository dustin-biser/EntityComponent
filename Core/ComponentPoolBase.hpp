//
// ComponentPoolBase.hpp
//


// Forward declare.
class GameObject;
class EntityID;


// Abstract base class for ComponentPools.
class ComponentPoolBase {
public:
	virtual void allocateComponent (
		const GameObject & gameObject
	) = 0;

	virtual void destroyComponent (
		const EntityID & id
	) = 0;

	virtual void setComponentActive (
		const EntityID & id,
		bool activate
	) = 0;

	virtual bool hasComponent (
		const EntityID & id
	) const = 0;

	// Returns the number of objects in active list.
	virtual size_t numActive() const = 0;
};