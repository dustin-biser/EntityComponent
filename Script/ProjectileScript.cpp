//
// ProjectileScript.cpp
//

#include "ProjectileScript.hpp"

#include <cstdlib>

//---------------------------------------------------------------------------------------
void ProjectileScript::init()
{
	Rendering & rendering = m_gameObject->addComponent<Rendering>();
	rendering.mesh = MeshDirectory::getMesh("Projectile");
	rendering.color = Color {1.0f, 1.0f, 1.0f};

	Transform & transform = m_gameObject->transform();
	float scale_x = (20.0f / Screen::width);
	float scale_y = (20.0f / Screen::height);
	transform.scale = vec2(scale_x, scale_y);

	Motion & motion = m_gameObject->addComponent<Motion>();
	motion.velocity = vec2(1.0f);
}

//---------------------------------------------------------------------------------------
void ProjectileScript::update()
{
	vec2 position = transform().position;
	if (position.x < -1.0f || position.x > 1.0f) {
		m_gameObject->destroy();
	}

	if (position.y < -1.0f || position.y > 1.0f) {
		m_gameObject->destroy();
	}

}
