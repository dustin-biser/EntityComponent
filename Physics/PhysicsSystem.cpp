//
// PhysicsSystem.cpp
//
#pragma once

#if false


#include <algorithm>
using std::min;

#include "Physics/PhysicsSystem.hpp"
#include "Physics/Physics.hpp"

#include "GameObject/ComponentPool.hpp"
#include "GameObject/GameObject.hpp"

#include "Assets/Mesh2d.hpp"

#include "Graphics/Rendering.hpp"

#include <list>
using std::list;

struct IntervalPoint {
	enum type {
		BEGIN,
		END
	}type;

	GameObjectID id;
	float value;
};

bool operator > (const IntervalPoint & a, const IntervalPoint & b)
{
	return a.value > b.value;
}



class PhysicsSystemImpl {
private:
	friend class PhysicsSystem;

	void update (
		ComponentPool * gameObjectPool
	);

	void computeBoundingBoxFor(GameObject & gameObject);


// Members:
	std::list<GameObjectID> activeList;
};


//---------------------------------------------------------------------------------------
PhysicsSystem::PhysicsSystem()
{
	impl = new PhysicsSystemImpl();

}

//---------------------------------------------------------------------------------------
PhysicsSystem::~PhysicsSystem()
{
	delete impl;
	impl = nullptr;
}

//---------------------------------------------------------------------------------------
void PhysicsSystemImpl::update (
	ComponentPool * gameObjectPool
) {
	activeList.clear();

	// Determine set of GameObjectIDs this frame, and remove nodes referencing
	// GameObjectIDs no longer present.


	// Compute BoundingBox for each GameObject
	GameObject * gameObject = gameObjectPool->beginActive();
	for (size_t i(0); i < gameObjectPool->numActive(); ++i) {
		computeBoundingBoxFor(gameObject[i]);
	}

	// Construct sorted intervals for x-axis.
	for (size_t i(0); i < gameObjectPool->numActive(); ++i) {

	}

	// Construct sorted intervals for y-axis.
}

//---------------------------------------------------------------------------------------
// Compute BoundingBox based on transformed vertices of gameObject.
void PhysicsSystemImpl::computeBoundingBoxFor (
	GameObject & gameObject
) {
	BoundingBox b = { vec2(FLT_MAX), vec2(FLT_MIN) };
	Transform transform = gameObject.transform;

	Vertex v;
	for (const auto & vertex : gameObject.graphics->mesh->vertexList) {
		v = transform * vertex;
		b.min.x = std::min(b.min.x, v.x);
		b.min.y = std::min(b.min.y, v.y);

		b.max.x = std::max(b.max.x, v.x);
		b.max.y = std::max(b.max.y, v.y);
	}

	gameObject.physics->boundingBox = b;
}


//---------------------------------------------------------------------------------------
void PhysicsSystem::update(
	ComponentPool * gameObjectPool
)
{
	impl->update(gameObjectPool);
}

#endif
