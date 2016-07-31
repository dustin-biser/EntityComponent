#include "C_Application.h"

#include <cstdlib>
using std::rand;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

#include "graphics.h"
#include "time.h"

#include "Assets/AssetDefinitions.hpp"
#include "Assets/AssetLoader.hpp"
#include "Assets/Mesh2d.hpp"

#include "Core/GameConstants.hpp"
#include "Core/GameObject.hpp"
#include "Core/Input.hpp"
#include "Core/Screen.hpp"

#include "Rendering/Rendering.hpp"
#include "Rendering/RenderingSystem.hpp"

#include "Script/Script.hpp"
#include "Script/ScriptSystem.hpp"
#include "Script/CannonScript.hpp"
#include "Script/ClockScript.hpp"



static vec2 randomPositionBetween (vec2 min, vec2 max); 



class C_ApplicationImpl {
private:
	friend class C_Application;

	std::unordered_map<MeshID, Mesh2d> meshAssetDirectory;

	C_ApplicationImpl (
		int screenWidth,
		int screenHeight
	);

	void buildMeshAssetDirectory();

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

	buildMeshAssetDirectory();

	loadGameObjects();

	ScriptSystem::init();
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::buildMeshAssetDirectory()
{
}


//---------------------------------------------------------------------------------------
//void C_ApplicationImpl::initGameObjectReplicators()
//{
#if false

	// Initialize clock replicator
	{
		Rendering * hourHandGraphics = new Rendering(
			Color{ 1.0f, 1.0f, 1.0f },
			&meshAssetDirectory.at("HourHand")
		);

		Rendering * minuteHandGraphics = new Rendering(
			Color{ 1.0f, 0.3f, 0.3f },
			&meshAssetDirectory.at("MinuteHand")
		);

		Rendering * secondHandGraphics = new Rendering(
			Color{ 0.8f, 0.8f, 0.2f },
			&meshAssetDirectory.at("SecondHand")
		);

		Rendering * clockBaseGraphics = new Rendering(
			Color{ 0.8f, 0.2f, 0.2f },
			&meshAssetDirectory.at("ClockBase")
		);

		Motion * clockHandMotion = new ClockHandMotionComponent();

		GameObject * hourHand = childGameObjectPool->create(GameObject::generateID());
		hourHand->graphics = hourHandGraphics;
		hourHand->motion = clockHandMotion;

		GameObject * minuteHand = childGameObjectPool->create(GameObject::generateID());
		minuteHand->graphics = minuteHandGraphics;
		minuteHand->motion = clockHandMotion;

		GameObject * secondHand = childGameObjectPool->create(GameObject::generateID());
		secondHand->graphics = secondHandGraphics;
		secondHand->motion = clockHandMotion;


		GameObject * clockPrototype = prototypePool->create(GameObject::generateID());

		clockPrototype->addChild(hourHand);
		clockPrototype->addChild(minuteHand);
		clockPrototype->addChild(secondHand);

		clockPrototype->graphics = clockBaseGraphics;

		float scale_x = (100.0f / m_ScreenWidth);
		float scale_y = (100.0f / m_ScreenHeight);
		clockPrototype->transform.scale = vec2(scale_x, scale_y);

		clockReplicator = new GameObjectReplicator(clockPrototype);
	}

	// Initialize projectile replicator
	{
		Rendering * projectileGraphicsComponent = new Rendering (
			Color{ 1.0f, 1.0f, 1.0f },
			&meshAssetDirectory.at("Projectile")
		);

		GameObject * projectilePrototype = prototypePool->create(GameObject::generateID());
		projectilePrototype->graphics = projectileGraphicsComponent;
		projectilePrototype->motion->velocity = vec2(0.0f, 1.5f);

		float scale_x = (30.0f / m_ScreenWidth);
		float scale_y = (30.0f / m_ScreenHeight);
		projectilePrototype->transform.scale = vec2(scale_x, scale_y);
		projectilePrototype->transform.position = vec2(-0.8f, 0.0f);

		projectileReplicator = new GameObjectReplicator(projectilePrototype);
	}
#endif
//}


//---------------------------------------------------------------------------------------
static vec2 randomPositionBetween (
	vec2 min,
	vec2 max
) {
	float t0 = rand() / static_cast<float>(RAND_MAX);
	float t1 = rand() / static_cast<float>(RAND_MAX);

	float x = (1.0f - t0) * min.x + t0 * max.x;
	float y = (1.0f - t1) * min.y + t1 * max.y;

	return vec2(x, y);
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::loadGameObjects()
{
	GameObject * cannon = new GameObject("Cannon");
	cannon->addComponent<CannonScript>();

	GameObject * clock = new GameObject("Clock");
	clock->addComponent<ClockScript>();
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::Tick (
	C_Application::T_PressedKey pressedKeys
) {
	handleInput(pressedKeys);

	ScriptSystem::update();

	RenderingSystem::renderScene();
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::handleInput (
	C_Application::T_PressedKey pressedKeys
) {
	Input::setKey(KEY::LEFT, (pressedKeys & C_Application::s_KeyLeft) > 0);
	Input::setKey(KEY::RIGHT, (pressedKeys & C_Application::s_KeyRight) > 0);
	Input::setKey(KEY::UP, (pressedKeys & C_Application::s_KeyUp) > 0);
	Input::setKey(KEY::DOWN, (pressedKeys & C_Application::s_KeyDown) > 0);
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

