//
// CannonScript.cpp
//
#include "CannonScript.hpp"


//---------------------------------------------------------------------------------------
void CannonScript::init()
{
	m_cannon = &gameObject();

	Rendering & rendering = m_cannon->addComponent<Rendering>();
	rendering.mesh = MeshDirectory::getMesh("Cannon");
	rendering.color = Color {0.2f, 0.2f, 1.0f};

	float scale_x = (60.0f / Screen::width);
	float scale_y = (60.0f / Screen::height);

	Transform & transform = m_cannon->transform();
	// Place cannon near bottom of screen.
	transform.position = vec2(0.0f, -0.8f);
	transform.scale = vec2(scale_x, scale_y);
}

//---------------------------------------------------------------------------------------
void CannonScript::update()
{

}

