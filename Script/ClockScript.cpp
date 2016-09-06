//
// ClockScript.cpp
//
#include "ClockScript.hpp"

#include "Core/time.h"
#include "Core/Utils.hpp"


//---------------------------------------------------------------------------------------
static vec2 randomPositionBetween (
	vec2 min,
	vec2 max
) {
	const float t0 = randFloat();
	const float t1 = randFloat();

	// Linearly interpolate between min and max.
	const float x = (1.0f - t0) * min.x + t0 * max.x;
	const float y = (1.0f - t1) * min.y + t1 * max.y;

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

		float aspect = static_cast<float>(Screen::width) / Screen::height;
		float scale_x = (100.0f / Screen::width);
		float scale_y = (100.0f / Screen::height);
		Transform & transform = m_clock->transform();
		transform.scale = vec2(scale_x, scale_y);
		transform.position = randomPositionBetween(vec2(-0.8f, 0.8f), vec2(-0.8f, 0.8f));

		Motion & motion = m_clock->addComponent<Motion>();
		motion.velocity = vec2(randFloat(), randFloat()) * 0.1f;

	}

	// Hour Hand
	{
		m_hourHand = new GameObject("HourHand");
		Rendering & rendering = m_hourHand->addComponent<Rendering>();
		rendering.mesh = MeshDirectory::getMesh(m_hourHand->getName());
		rendering.color = Color {1.0f, 1.0f, 1.0f};
	}

	// Minute Hand
	{
		m_minuteHand = new GameObject("MinuteHand");
		Rendering & rendering = m_minuteHand->addComponent<Rendering>();
		rendering.mesh = MeshDirectory::getMesh(m_minuteHand->getName());
		rendering.color = Color {0.8f, 0.2f, 0.8f};
	}

	// Second Hand
	{
		m_secondHand = new GameObject("SecondHand");
		Rendering & rendering = m_secondHand->addComponent<Rendering>();
		rendering.mesh = MeshDirectory::getMesh(m_secondHand->getName());
		rendering.color = Color{ 0.6f, 0.6f, 0.2f };
	}

	m_hourHand->setParent(*m_clock);
	m_minuteHand->setParent(*m_clock);
	m_secondHand->setParent(*m_clock);
}

//---------------------------------------------------------------------------------------
void ClockScript::update()
{
	int hour, minute, second;
	GetTime(hour, minute, second);

	//-- Update clock hand positions based on current time:
	{
		const float twoPI = 2.0f * k_PI;
		const float secondRatio = (second / 60.0f);
		const float minuteRatio = (minute / 60.0f);
		m_hourHand->transform().rotationAngle = -1.0f * ((hour + minuteRatio) / 12.0f) * twoPI;
		m_minuteHand->transform().rotationAngle = -1.0f * ((minute + secondRatio) / 60.0f) * twoPI;
		m_secondHand->transform().rotationAngle = -1.0f * secondRatio * twoPI;
	}


	//// Replicate ClockScript, which clones it's owning GameObject, and
	//// GameObjects from child Transforms.
	//ClockScript & newClockScript = Entity::replicate<ClockScript>(*this);
	//newClockScript.m_clock = &newClockScript.gameObject();
	//newClockScript.m_hourHand = &newClockScript.transform().childAtIndex(0)->gameObject();
	//newClockScript.m_minuteHand = &newClockScript.transform().childAtIndex(1)->gameObject();
	//newClockScript.m_secondHand = &newClockScript.transform().childAtIndex(2)->gameObject();
}