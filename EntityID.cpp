//
// EntityID.cpp
//

#include "EntityID.hpp"


EntityID generateEntityID()
{
	static EntityID nextID(0);
	return nextID++;
}
