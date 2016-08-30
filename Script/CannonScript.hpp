//
// CannonScript.hpp
//
#pragma once

#include "Script/Script.hpp"

class CannonScript : public Script {
public:

	void init() override;

	void update() override;



private:

	void spawnProjectile();

	GameObject * m_cannon;
	GameObject * m_projectile;

	Vertex m_vertexTipOfCannon;
};