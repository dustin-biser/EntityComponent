//
// ComponentSystemLocator.hpp
//
#pragma once

// Forward declare
template <class T>
class ComponentSystem;


template <class T>
class ComponentSystemLocator {
public:
	static ComponentSystem<T> * getSystem();

	static ComponentSystem<T> * provide(ComponentSystem<T> * componentSystem);

private:
	static ComponentSystem<T> * requestedService;

};


#include "ComponentSystemLocator.inl"