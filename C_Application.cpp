#include "C_Application.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

#include "graphics.h"
#include "time.h"

#include "Assets\AssetDefinitions.hpp"
#include "AssetLoader.hpp"
#include "Mesh2d.hpp"
#include "GameObject.hpp"
#include "GameObjectPool.hpp"
#include "GameObjectReplicator.hpp"
#include "GraphicsSystem.hpp"
#include "GraphicsComponent.hpp"


static const float k_PI = 3.1415926536f;

static const size_t MAX_GAME_OBJECTS       = 1024;
static const size_t MAX_CHILD_GAME_OBJECTS = 1024;
static const size_t MAX_PROTOTYPE_OBJECTS  = 3;



class C_ApplicationImpl {
private:
	friend class C_Application;

	const int m_ScreenWidth;
	const int m_ScreenHeight;

	// TODO - Move these into Cannon GameObject
	int	m_CannonX;
	int	m_CannonY;

	std::unordered_map<MeshId, Mesh2d> meshAssetDirectory;

	GameObjectPool * gameObjectPool;
	GameObjectPool * childGameObjectPool;
	GameObjectPool * prototypePool;

	GameObjectID cannon_id;

	GameObjectID clockPrototype_id;
	GameObjectID projectilePrototype_id;


	GraphicsSystem * graphicsSystem;

	C_ApplicationImpl (
		int screenWidth,
		int screenHeight
	);

	void buildMeshAssetDirectory();

	void initGameObjectPools();

	void initGameObjectPrototypes();

	void initSubSystems();

	void loadGameObjects();

	void Tick (
		C_Application::T_PressedKey pressedKeys
	);


};

//---------------------------------------------------------------------------------------
C_ApplicationImpl::C_ApplicationImpl(
	int screenWidth,
	int screenHeight
) 
	: m_ScreenWidth(screenWidth),
	  m_ScreenHeight(screenHeight),
	  m_CannonX(m_ScreenWidth / 2),
	  m_CannonY(m_ScreenHeight / 2)
{
	buildMeshAssetDirectory();

	initGameObjectPools();

	initGameObjectPrototypes();

	initSubSystems();

	loadGameObjects();
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::buildMeshAssetDirectory()
{
	Asset::Definition assetDefinitions[] = {
		Asset::Cannon,
		Asset::Projectile,
		Asset::ClockBase,
		Asset::HourHand,
		Asset::MinuteHand,
		Asset::SecondHand
	};

	for (auto asset : assetDefinitions) {
		Mesh2d mesh;
		AssetLoader::decodeMesh(asset, mesh);
		meshAssetDirectory[mesh.meshId] = std::move(mesh);
	}
}


//---------------------------------------------------------------------------------------
void C_ApplicationImpl::initGameObjectPools()
{
	gameObjectPool = new GameObjectPool(MAX_GAME_OBJECTS);
	childGameObjectPool = new GameObjectPool(MAX_GAME_OBJECTS);
	prototypePool = new GameObjectPool(MAX_PROTOTYPE_OBJECTS);
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::initGameObjectPrototypes()
{
	// Construct Clock Prototype
	{
		GraphicsComponent * hourHandGraphicsComponent = new GraphicsComponent(
			Color{ 1.0f, 1.0f, 1.0f },
			&meshAssetDirectory.at("HourHand")
		);

		GraphicsComponent * minuteHandGraphicsComponent = new GraphicsComponent(
			Color{ 1.0f, 0.3f, 0.3f },
			&meshAssetDirectory.at("MinuteHand")
		);

		GraphicsComponent * secondHandGraphicsComponent = new GraphicsComponent(
			Color{ 0.8f, 0.8f, 0.2f },
			&meshAssetDirectory.at("SecondHand")
		);

		GraphicsComponent * clockGraphicsComponent = new GraphicsComponent(
			Color{ 0.8f, 0.2f, 0.2f },
			&meshAssetDirectory.at("ClockBase")
		);

		GameObject * hourHand = new GameObject();
		hourHand->graphics = hourHandGraphicsComponent;
		hourHand->transform.rotationAngle = k_PI * 0.1f;

		GameObject * minuteHand = new GameObject();
		minuteHand->graphics = minuteHandGraphicsComponent;
		minuteHand->transform.rotationAngle = k_PI * 0.2f;

		GameObject * secondHand = new GameObject();
		secondHand->graphics = secondHandGraphicsComponent;
		secondHand->transform.rotationAngle = k_PI * 0.3f;


		clockPrototype_id = GameObject::generateID();
		prototypePool->create(clockPrototype_id);
		prototypePool->destroy(clockPrototype_id);
		GameObject * clock = prototypePool->create(clockPrototype_id);


		clock->graphics = clockGraphicsComponent;

		clock->childObjects.push_back(hourHand);
		clock->childObjects.push_back(minuteHand);
		clock->childObjects.push_back(secondHand);

		float scale_x = (100.0f / m_ScreenWidth);
		float scale_y = (100.0f / m_ScreenHeight);
		clock->transform.scale = vec2(scale_x, scale_y);
	}

	// Construct Projectile Prototype
	{
		GraphicsComponent * projectileGraphicsComponent = new GraphicsComponent (
			Color{ 1.0f, 1.0f, 1.0f },
			&meshAssetDirectory.at("Projectile")
		);

		projectilePrototype_id = GameObject::generateID();
		GameObject * projectile = prototypePool->create(projectilePrototype_id);
		projectile->graphics = projectileGraphicsComponent;

		float scale_x = (30.0f / m_ScreenWidth);
		float scale_y = (30.0f / m_ScreenHeight);
		projectile->transform.scale = vec2(scale_x, scale_y);
		projectile->transform.position = vec2(-0.8f, 0.0f);
	}
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::initSubSystems()
{
	graphicsSystem = new GraphicsSystem();
	graphicsSystem->setViewport(0, 0, m_ScreenWidth, m_ScreenHeight);
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::loadGameObjects()
{
	// Create Cannon
	{
		cannon_id = GameObject::generateID();
		GameObject * cannon = gameObjectPool->create(cannon_id);
		cannon->graphics = new GraphicsComponent(
			Color{ 0.2f, 0.2f, 1.0f },
			&meshAssetDirectory.at("Cannon")
		);
		float scale_x = (60.0f / m_ScreenWidth);
		float scale_y = (60.0f / m_ScreenHeight);
		cannon->transform.scale = vec2(scale_x, scale_y);
		cannon->transform.position = vec2(0.0f, -0.8f);
	}
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::Tick (
	C_Application::T_PressedKey pressedKeys
) {
	graphicsSystem->clearScreen(m_ScreenWidth, m_ScreenHeight);
	graphicsSystem->drawGameObjects(gameObjectPool->begin(), gameObjectPool->numActive());
	graphicsSystem->drawGameObjects(prototypePool->begin(), prototypePool->numActive());


	// Key processing
	if(pressedKeys & C_Application::s_KeyLeft)
	{
		m_CannonX = max(0, m_CannonX-4);
	}

	if(pressedKeys & C_Application::s_KeyRight)
	{
		m_CannonX = min(m_ScreenWidth, m_CannonX+4);
	}

	if(pressedKeys & C_Application::s_KeyUp)
	{
		m_CannonY = max(0, m_CannonY-4);
	}

	if(pressedKeys & C_Application::s_KeyDown)
	{
		m_CannonY = min(m_ScreenHeight, m_CannonY+4);
	}

	if(pressedKeys & C_Application::s_KeySpace)
	{
	}

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
	impl = nullptr;
}


//---------------------------------------------------------------------------------------
void C_Application::Tick(T_PressedKey pressedKeys)
{
	impl->Tick(pressedKeys);
}

