//
// ProjectileScript.cpp
//

#include "ProjectileScript.hpp"

#include <cstdlib>

#include "time.h"

static float randFloat()
{
	int hr, min, sec;
	GetTime(hr, min, sec);
	srand(sec);
	return rand() / static_cast<float>(RAND_MAX);
}

//---------------------------------------------------------------------------------------
void ProjectileScript::init()
{
	m_projectile = &gameObject();
	Rendering & rendering = m_projectile->addComponent<Rendering>();
	rendering.mesh = MeshDirectory::getMesh("Projectile");
	rendering.color = Color {1.0f, 1.0f, 1.0f};

	float scale_x = (50.0f / Screen::width);
	float scale_y = (50.0f / Screen::height);

	Transform & transform = m_projectile->transform();
	transform.position = vec2(0.0f, 0.0f) + vec2(randFloat(), randFloat());
	transform.scale = vec2(scale_x, scale_y);
}

//---------------------------------------------------------------------------------------
void ProjectileScript::update()
{
	//Transform & transform = this->transform();
	//transform.position += vec2(0.01f, 0.0f);
}
