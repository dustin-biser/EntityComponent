//
// ProjectileScript.hpp
//
#pragma once

#include "Script/Script.hpp"


class ProjectileScript : public Script {
public:

	void init() override;

	void update() override;


private:
	GameObject * m_projectile;
};

