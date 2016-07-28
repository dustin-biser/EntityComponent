//
// Component.cpp
//

#include "Component.hpp"


#define MAX_POINTERS sizeof(size_t)

// Pointer table is used as a virtual address system due to how Components
// are moved in memory from within their respective ComponentPools for optimization
// purposes.
//
// The pointer table keeps track of the updated memory location of each Component
// instance. Each instance is given a unique pointerTableIndex into the table
// so that it can retrieve itself from client side Component * pointers.
static Component * pointerTable[MAX_POINTERS];
size_t currentTableIndex = 0;


//---------------------------------------------------------------------------------------
Component::Component (
	EntityID id,
	GameObject & gameObject
) 
	: Entity(id),
	  gameObject(gameObject),
	  pointerTableIndex(currentTableIndex++) // Assign unique pointer table index.
{
	// Register instance address with pointer table.
	pointerTable[pointerTableIndex] = this;
}

//---------------------------------------------------------------------------------------
Component::~Component()
{

}

//---------------------------------------------------------------------------------------
Component * Component::operator -> () const
{
	return pointerTable[this->pointerTableIndex];
}

//---------------------------------------------------------------------------------------
Component & Component::operator * () const
{
	return *pointerTable[this->pointerTableIndex];
}

//---------------------------------------------------------------------------------------
void Component::updatePointerTableEntry (
	Component * newAddress
) {
	pointerTable[this->pointerTableIndex] = newAddress;
}

