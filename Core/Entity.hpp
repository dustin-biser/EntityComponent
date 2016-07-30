//
// Entity.hpp
//
#pragma once

#include "Core/EntityID.hpp"


// Base class for all stateful game objects.
class Entity {
public:

	Entity();

	Entity(EntityID id);

	EntityID getEntityID() const;


protected:
	EntityID id;
};
