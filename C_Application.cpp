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

	// Allocation Pools
	GameObjectPool * gameObjectPool;
	GameObjectPool * childGameObjectPool;
	GameObjectPool * prototypePool;

	GameObjectID cannon_id;

	GameObjectReplicator * clockReplicator;
	GameObjectReplicator * projectileReplicator;


	// Subsystems
	GraphicsSystem * graphicsSystem;

	C_ApplicationImpl (
		int screenWidth,
		int screenHeight
	);

	void buildMeshAssetDirectory();

	void initGameObjectPools();

	void initGameObjectReplicators();

	void initSubSystems();

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
) 
	: m_ScreenWidth(screenWidth),
	  m_ScreenHeight(screenHeight),
	  m_CannonX(m_ScreenWidth / 2),
	  m_CannonY(m_ScreenHeight / 2)
{
	buildMeshAssetDirectory();

	initGameObjectPools();

	initGameObjectReplicators();

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
void C_ApplicationImpl::initGameObjectReplicators()
{
	// Initialize clock replicator
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

		GameObject * hourHand = childGameObjectPool->create(GameObject::generateID());
		hourHand->graphics = hourHandGraphicsComponent;

		GameObject * minuteHand = childGameObjectPool->create(GameObject::generateID());
		minuteHand->graphics = minuteHandGraphicsComponent;

		GameObject * secondHand = childGameObjectPool->create(GameObject::generateID());
		secondHand->graphics = secondHandGraphicsComponent;


		GameObject * clockPrototype = prototypePool->create(GameObject::generateID());

		clockPrototype->addChild(hourHand);
		clockPrototype->addChild(minuteHand);
		clockPrototype->addChild(secondHand);

		clockPrototype->graphics = clockGraphicsComponent;

		float scale_x = (100.0f / m_ScreenWidth);
		float scale_y = (100.0f / m_ScreenHeight);
		clockPrototype->transform.scale = vec2(scale_x, scale_y);

		clockReplicator = new GameObjectReplicator(clockPrototype);
	}

	// Initialize projectile replicator
	{
		GraphicsComponent * projectileGraphicsComponent = new GraphicsComponent (
			Color{ 1.0f, 1.0f, 1.0f },
			&meshAssetDirectory.at("Projectile")
		);

		GameObject * projectilePrototype = prototypePool->create(GameObject::generateID());
		projectilePrototype->graphics = projectileGraphicsComponent;

		float scale_x = (30.0f / m_ScreenWidth);
		float scale_y = (30.0f / m_ScreenHeight);
		projectilePrototype->transform.scale = vec2(scale_x, scale_y);
		projectilePrototype->transform.position = vec2(-0.8f, 0.0f);

		projectileReplicator = new GameObjectReplicator(projectilePrototype);
	}
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::initSubSystems()
{
	graphicsSystem = new GraphicsSystem();
	graphicsSystem->setViewport(0, 0, m_ScreenWidth, m_ScreenHeight);
}

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
	// Load Cannon
	{
		// Keep track of cannon for later use.
		this->cannon_id = GameObject::generateID();

		GameObject * cannon = gameObjectPool->create(cannon_id);
		cannon->graphics = new GraphicsComponent (
			Color{ 0.2f, 0.2f, 1.0f },
			&meshAssetDirectory.at("Cannon")
		);
		float scale_x = (60.0f / m_ScreenWidth);
		float scale_y = (60.0f / m_ScreenHeight);
		cannon->transform.scale = vec2(scale_x, scale_y);

		// Place cannon near bottom of screen.
		cannon->transform.position = vec2(0.0f, -0.8f);
	}

	// Load 2 Clocks in random positions
	{
		GameObject * clock1 = clockReplicator->replicateInto(gameObjectPool);
		clock1->transform.position = randomPositionBetween(vec2(-0.7f, 0.0f), vec2(-0.2f, 0.8f));

		GameObject * clock2 = clockReplicator->replicateInto(gameObjectPool);
		clock2->transform.position = randomPositionBetween(vec2(0.2f, 0.0f), vec2(0.7f, 0.8f));
	}
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::Tick (
	C_Application::T_PressedKey pressedKeys
) {
	handleInput(pressedKeys);

	graphicsSystem->clearScreen(m_ScreenWidth, m_ScreenHeight);
	graphicsSystem->drawGameObjects(gameObjectPool->begin(), gameObjectPool->numActive());
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::handleInput (
	C_Application::T_PressedKey pressedKeys
) {
	const float deltaAngle = 0.1f;
	const float maxAngle = k_PI * 0.5f;
	const float minAngle = -maxAngle;

	if (pressedKeys & C_Application::s_KeyLeft) {
		GameObject * cannon = gameObjectPool->getObject(cannon_id);
		float & rotationAngle = cannon->transform.rotationAngle;
		rotationAngle += deltaAngle;
		rotationAngle = min(maxAngle, rotationAngle);
	}
	
	if (pressedKeys & C_Application::s_KeyRight) {
		GameObject * cannon = gameObjectPool->getObject(cannon_id);
		float & rotationAngle = cannon->transform.rotationAngle;
		rotationAngle -= deltaAngle;
		rotationAngle = max(minAngle, rotationAngle);
	}

	if (pressedKeys & C_Application::s_KeyUp) {
	}

	if (pressedKeys & C_Application::s_KeyDown) {
	}

	if (pressedKeys & C_Application::s_KeySpace) {
		//-- Position projectiles to be at tip of cannon.
		{
			GameObject * projectilePrototype = projectileReplicator->getPrototype();
			GameObject * cannon = gameObjectPool->getObject(cannon_id);

			Vertex vertex = cannon->graphics->mesh->vertexList[2];
			Transform cannonTransform = cannon->transform;
			vertex = GraphicsSystem::transformVertex(vertex, cannonTransform);

			projectilePrototype->transform.position = vertex;
			projectilePrototype->transform.rotationAngle = cannonTransform.rotationAngle;

			// Update velocity direction of projectile.
			//vec2 direction = normalize(vertex - cannon->transform.position);
			//vec2 vel = projectilePrototype->motion.velocity;
			//projectilePrototype->motion.velocity = direction * length(vel);
		}

		// Generate projectile
		projectileReplicator->replicateInto(gameObjectPool);
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

