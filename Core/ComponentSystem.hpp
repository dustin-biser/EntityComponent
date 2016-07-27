//
// ComponentSystem.hpp
//
#pragma once

#include "Core/EntityID.hpp"
#include "Core/SmartPointer.hpp"

template <class T>
class ComponentSystem {
public:
	ComponentSystem();

	void createComponent(EntityID id);

	SmartPointer<T> getComponent(EntityID id);
};


#include "ComponentSystem.inl"