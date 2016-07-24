//
// GameObjectPool.hpp
//

#include "GameObject.hpp"


// Forward declare.
class GameObjectPoolImpl;


// Type T must include a field named 'id' of type EntityID.
class GameObjectPool {
public:
	GameObjectPool(size_t numElements);
	~GameObjectPool();

	GameObject * create(GameObjectID id);

	// Caution: calling destory() will likely invalidate all pointers
	// previously returned by GameObjectPool.
	// Call GameObjectPool::getObject() after each call of
	// GameObjectPool::destory() in order to keep pointers valid.
	void destroy(GameObjectID id);

	GameObject * getObject(GameObjectID id);

	// Returns pointer to first element of pool.
	GameObject * begin() const;

	// Returns the number of alive objects in pool.
	size_t numActive() const;

private:
	GameObjectPoolImpl * impl;
};
