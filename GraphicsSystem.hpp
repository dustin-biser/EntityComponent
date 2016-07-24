//
// GraphicsSystem.hpp
//
#pragma once

// Forward declare.
class GraphicsSystemImpl;
class GameObject;


class GraphicsSystem {
public:
	GraphicsSystem();
	~GraphicsSystem();

	// Adjusts viewport transformation for drawn scene.
	// Arguments given in screen pixels.
	void setViewport (
		int x, int y,
		int width, int height
	);

	void drawScene (
		GameObject * gameObjects,
		size_t numGameObjects
	);


private:
	GraphicsSystemImpl * impl;
};

