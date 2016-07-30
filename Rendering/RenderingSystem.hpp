//
// RenderingSystem.hpp
//
#pragma once

#if false

#include "Mesh2d.hpp"

// Forward declare.
class GraphicsSystemImpl;
class GameObject;
struct Transform;


class RenderingSystem {
public:
	RenderingSystem();

	~RenderingSystem();

	// Adjusts viewport transformation for drawn scene.
	// Arguments given in screen pixels.
	void setViewport (
		int x, int y,
		int width, int height
	);

	void drawGameObjects (
		GameObject * gameObjects,
		size_t numGameObjects
	);

	void clearScreen (
		int screenWidth,
		int screenHeight
	) const;


private:
	GraphicsSystemImpl * impl;
};


#endif