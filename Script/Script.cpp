//
// Script.cpp
//
#include "Script.hpp"


//---------------------------------------------------------------------------------------
Script::Script (
	EntityID id,
	GameObject & gameObject
)
	: Component(id, gameObject),
	  scriptBehavior(nullptr)
{

}

//---------------------------------------------------------------------------------------
Script::~Script()
{
	delete scriptBehavior;
}

//---------------------------------------------------------------------------------------
void Script::onUpdate()
{

}

//---------------------------------------------------------------------------------------
void Script::onCollision()
{

}
