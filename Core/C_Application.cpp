#include "C_Application.h"

#include "graphics.h"
#include "time.h"

#include "Core/GameObject.hpp"
#include "Core/Input.hpp"
#include "Core/Screen.hpp"

#include "Motion/MotionSystem.hpp"

#include "Rendering/Rendering.hpp"
#include "Rendering/RenderingSystem.hpp"

#include "Script/Script.hpp"
#include "Script/ScriptSystem.hpp"
#include "Script/CannonScript.hpp"
#include "Script/ClockScript.hpp"



class C_ApplicationImpl {
private:
	friend class C_Application;

	C_ApplicationImpl (
		int screenWidth,
		int screenHeight
	);

	void loadGameObjects();

	void Tick (
		C_Application::T_PressedKey pressedKeys
	);

	void handleInput (
		C_Application::T_PressedKey pressedKeys
	);

};

//---------------------------------------------------------------------------------------
C_ApplicationImpl::C_ApplicationImpl(
	int screenWidth,
	int screenHeight
) {
	Screen::width = screenWidth;
	Screen::height = screenHeight;

	RenderingSystem::setViewport(0, 0, screenWidth, screenHeight);

	loadGameObjects();
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::loadGameObjects()
{
	GameObject * cannon = new GameObject("Cannon");
	cannon->addComponent<CannonScript>();

	GameObject * clock1 = new GameObject("Clock1");
	clock1->addComponent<ClockScript>();

	GameObject * clock2 = new GameObject("Clock2");
	clock2->addComponent<ClockScript>();
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::Tick (
	C_Application::T_PressedKey pressedKeys
) {
	handleInput(pressedKeys);

	ScriptSystem::update();

	// TODO - Replace with actual std::chrono time delta computation.
	float ellapsedTimeInSeconds = 1.0f / 50.0f;
	MotionSystem::update(ellapsedTimeInSeconds);

	RenderingSystem::renderScene();
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::handleInput (
	C_Application::T_PressedKey pressedKeys
) {
	Input::setKey(KEY::LEFT,  (pressedKeys & C_Application::s_KeyLeft)  > 0);
	Input::setKey(KEY::RIGHT, (pressedKeys & C_Application::s_KeyRight) > 0);
	Input::setKey(KEY::UP,    (pressedKeys & C_Application::s_KeyUp)    > 0);
	Input::setKey(KEY::DOWN,  (pressedKeys & C_Application::s_KeyDown)  > 0);
	Input::setKey(KEY::SPACE, (pressedKeys & C_Application::s_KeySpace) > 0);
}

//---------------------------------------------------------------------------------------
C_Application::C_Application (
	int screenWidth,
	int screenHeight
) {
	impl = new C_ApplicationImpl(screenWidth, screenHeight);
}


//---------------------------------------------------------------------------------------
C_Application::~C_Application()
{
	delete impl;
}


//---------------------------------------------------------------------------------------
void C_Application::Tick(T_PressedKey pressedKeys)
{
	impl->Tick(pressedKeys);
}

