//
// ClockScript.cpp
//
#include "ClockScript.hpp"


//---------------------------------------------------------------------------------------
static vec2 randomPositionBetween (
	vec2 min,
	vec2 max
)
{
	float t0 = rand() / static_cast<float>(RAND_MAX);
	float t1 = rand() / static_cast<float>(RAND_MAX);

	float x = (1.0f - t0) * min.x + t0 * max.x;
	float y = (1.0f - t1) * min.y + t1 * max.y;

	return vec2(x, y);
}


//---------------------------------------------------------------------------------------
void ClockScript::init()
{
	// Clock Base
	{
		m_clock = &gameObject();
		Rendering & rendering = m_clock->addComponent<Rendering>();
		rendering.mesh = MeshDirectory::getMesh("ClockBase");
		rendering.color = Color {1.0f, 0.3f, 0.3f};

		Transform & transform = m_clock->transform();
		float scale_x = (100.0f / Screen::width);
		float scale_y = (100.0f / Screen::height);
		transform.scale = vec2(scale_x, scale_y);
		transform.position = vec2(0.0f, 0.0f);
	}

	// Hour Hand
	{
		m_hourHand = new GameObject("HourHand");
		Rendering & rendering = m_hourHand->addComponent<Rendering>();
		rendering.mesh = MeshDirectory::getMesh(m_hourHand->name);
		rendering.color = Color {1.0f, 1.0f, 1.0f};

		m_hourHand->transform().setParent(m_clock->transform());
	}

	// Minute Hand
	{
		m_minuteHand = new GameObject("MinuteHand");
		Rendering & rendering = m_minuteHand->addComponent<Rendering>();
		rendering.mesh = MeshDirectory::getMesh(m_minuteHand->name);
		rendering.color = Color {1.0f, 0.3f, 0.3f};

		m_minuteHand->transform().setParent(m_clock->transform());
	}

	// Second Hand
	{
		m_secondHand = new GameObject("SecondHand");
		Rendering & rendering = m_secondHand->addComponent<Rendering>();
		rendering.mesh = MeshDirectory::getMesh(m_secondHand->name);
		rendering.color = Color{ 0.8f, 0.8f, 0.2f };

		m_secondHand->transform().setParent(m_clock->transform());
	}
}

//---------------------------------------------------------------------------------------
void ClockScript::update()
{

}