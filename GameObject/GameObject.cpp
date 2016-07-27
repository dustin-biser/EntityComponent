//
// GameObject.cpp
//
#include "GameObject.hpp"

#include "Core/ComponentSystemLocator.hpp"
#include "Core/ComponentSystem.hpp"
#include "Core/Transform.hpp"

GameObject::GameObject(const std::string & name)
	: id(EntityID::generateID()),
	  name(name)
{
	ComponentSystem<Transform> * transformSystem = ComponentSystemLocator<Transform>::getSystem();
	transformSystem->createComponent(id);
}
