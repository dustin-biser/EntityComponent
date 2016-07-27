//
// GameObject.hpp
//
#pragma once

#include <string>

#include "Core/EntityID.hpp"
#include "Core/SmartPointer.hpp"


class GameObject {
public:
	GameObject (
		const std::string & name
	);

	template <class T>
	void addComponent();

	template <class T>
	SmartPointer<T> getComponent();

private:
	EntityID id;
	std::string name;
};


#include "GameObject.inl"