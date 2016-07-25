//
// PhysicsComponent.hpp
//
#pragma once


class PhysicsComponent {
public:
	PhysicsComponent();

	virtual ~PhysicsComponent();

	PhysicsComponent * clone() const;

};