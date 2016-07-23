#include "C_Application.h"
#include "graphics.h"
#include "time.h"

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <unordered_map>
using std::unordered_map;

#include "Assets\AssetDefinitions.hpp"
#include "AssetLoader.hpp"
#include "Mesh2d.hpp"
#include "GameObject.hpp"
#include "GraphicsComponent.hpp"
#include "ObjectPool.hpp"


static const float k_PI = 3.1415926536f;



class C_ApplicationImpl {
private:
	friend class C_Application;

	const int m_ScreenWidth;
	const int m_ScreenHeight;

	// TODO - Move these into Cannon GameObject
	int	m_CannonX;
	int	m_CannonY;

	std::unordered_map<MeshId, Mesh2d> meshAssetDirectory;


	C_ApplicationImpl (
		int screenWidth,
		int screenHeight
	);

	void buildMeshAssetDirectory();
	void initGraphicsObjects();

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
	 initGraphicsObjects();
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::buildMeshAssetDirectory()
{
	Asset::Definition assetDefinitions[] = {
		Asset::Cannon,
		Asset::Clock,
		Asset::Projectile
	};

	for (auto asset : assetDefinitions) {
		Mesh2d mesh;
		AssetLoader::decodeMesh(asset, mesh);
		meshAssetDirectory[mesh.meshId] = std::move(mesh);
	}
}


//---------------------------------------------------------------------------------------
void C_ApplicationImpl::initGraphicsObjects()
{
	GraphicsComponent cannonGraphicsComponent{
		Color{ 0.0f, 0.1f, 1.0f },
		&meshAssetDirectory.at("Cannon")
	};

	GameObject cannon (&cannonGraphicsComponent);

	////////////////////////////////////////////////////////////
	// TODO - Remove after testing
	const int NUM_OBJECTS(4);
	ObjectPool<GraphicsComponent, NUM_OBJECTS> graphicsObjPool;
	GraphicsComponent * graphics;
	for(int i(0); i < NUM_OBJECTS; ++i) {
		graphicsObjPool.create(EntityID(i));
		graphics = graphicsObjPool.getObject(EntityID(i));
		graphics->color.red = (i+1) * 0.1f;
	}
	for(int i(0); i < NUM_OBJECTS; ++i) {
		graphicsObjPool.destroy(EntityID(i));
	}
	////////////////////////////////////////////////////////////
}

//---------------------------------------------------------------------------------------
void C_ApplicationImpl::Tick (
	C_Application::T_PressedKey pressedKeys
) {
	// Sample tick

	// Clear screen on cannon position

	//FillRect(m_CannonX-10, m_CannonY, 21, 31, GetRGB(0, 0, 0));

	// Clear the screen
	FillRect(0,0, m_ScreenWidth, m_ScreenHeight, 0);

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

	// Draw cannon
	DrawLine(m_CannonX,    m_CannonY,    m_CannonX-10, m_CannonY+30, GetRGB(40,  40, 255));
	DrawLine(m_CannonX,    m_CannonY,    m_CannonX+10, m_CannonY+30, GetRGB(40, 40, 255));
	DrawLine(m_CannonX-10, m_CannonY+30, m_CannonX+10, m_CannonY+30, GetRGB(40, 40, 255));
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
