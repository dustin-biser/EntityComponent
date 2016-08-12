//
// Script.cpp
//
#include "Script.hpp"

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"

//---------------------------------------------------------------------------------------
Script::Script()
{

}

//---------------------------------------------------------------------------------------
Script::Script (
	const GameObject & gameObject
)
	: Component(gameObject)
{

}

//---------------------------------------------------------------------------------------
Script::~Script()
{

}
