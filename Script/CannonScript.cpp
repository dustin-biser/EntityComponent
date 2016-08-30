//
// CannonScript.cpp
//
#include "CannonScript.hpp"

#include "Script/ProjectileScript.hpp"

// TODO - Remove after testing.
#include "Core/ComponentPoolLocator.hpp"


#include <algorithm>
using std::max;
using std::min;


//---------------------------------------------------------------------------------------
void CannonScript::init()
{
	// Initialize Cannon GameObject.
	{
		m_cannon = &(this->gameObject());
		Rendering & rendering = m_cannon->addComponent<Rendering>();
		rendering.mesh = MeshDirectory::getMesh("Cannon");
		rendering.color = Color {0.2f, 0.2f, 1.0f};

		float scale_x = (60.0f / Screen::width);
		float scale_y = (60.0f / Screen::height);

		Transform & transform = m_cannon->transform();
		// Place m_cannon near bottom of screen.
		transform.position = vec2(0.0f, -0.8f);
		transform.scale = vec2(scale_x, scale_y);
	}

	// Initialize Projectile prototype. 
	{
		m_projectile = new GameObject("Projectile");
		m_projectile->addComponent<ProjectileScript>();
		m_projectile->setActive(false);
	}

	// Get vertex at tip of cannon.
	m_vertexTipOfCannon = m_cannon->getComponent<Rendering>()->mesh->vertexList[2];
}

//---------------------------------------------------------------------------------------
void CannonScript::update()
{
	const float deltaAngle = 0.05f;
	const float maxAngle = k_PI * 0.5f;
	float & rotationAngle = transform().rotationAngle;

	if (Input::keyDown(KEY::LEFT)) {
		rotationAngle += deltaAngle;
		rotationAngle = std::min(rotationAngle, maxAngle);
	}
	else if (Input::keyDown(KEY::RIGHT)) {
		rotationAngle -= deltaAngle;
		rotationAngle = std::max(rotationAngle, -maxAngle);
	}

	if (Input::keyDown(KEY::SPACE)) {
		spawnProjectile();
	}
}

//---------------------------------------------------------------------------------------
void CannonScript::spawnProjectile()
{
	GameObject & projectile = Entity::replicate(*m_projectile);

	Transform & cannonTransform = m_cannon->transform();
	Vertex vertex = cannonTransform * m_vertexTipOfCannon;

	// Update projectile's position and orientation
	Transform & transform = projectile.transform();
	transform.position = vertex;
	transform.rotationAngle = cannonTransform.rotationAngle;
}

