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
		Rendering & rendering = m_gameObject->addComponent<Rendering>();
		rendering.mesh = MeshDirectory::getMesh("Cannon");
		rendering.color = Color {0.2f, 0.2f, 1.0f};

		float scale_x = (60.0f / Screen::width);
		float scale_y = (60.0f / Screen::height);

		Transform & transform = m_gameObject->transform();
		// Place m_gameObject near bottom of screen.
		transform.position = vec2(0.0f, -0.8f);
		transform.scale = vec2(scale_x, scale_y);
	}

	// Initialize Projectile prototype. 
	{
		m_projectilePrototype = new GameObject("Projectile");
		m_projectilePrototype->addComponent<ProjectileScript>();
		m_projectilePrototype->setActive(false);
	}

	// Get vertex at tip of cannon.
	m_vertexTipOfCannon = m_gameObject->getComponent<Rendering>()->mesh->vertexList[2];
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
	GameObject & projectile = Entity::replicate(*m_projectilePrototype);

	Transform & cannonTransform = m_gameObject->transform();
	Vertex vertex = cannonTransform * m_vertexTipOfCannon;

	// Update projectile's position and orientation to be located at tip of cannon.
	Transform & transform = projectile.transform();
	transform.position = vertex;
	transform.rotationAngle = cannonTransform.rotationAngle;

	// Update projectile's velocity direction.
	vec2 direction = normalize(vertex - cannonTransform.position);
	Motion & projectileMotion = *projectile.getComponent<Motion>();

	vec2 vel = projectileMotion.velocity;
	projectileMotion.velocity = direction * length(vel);
}

