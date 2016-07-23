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

	void drawScene (
		GameObject * gameObjects,
		size_t numGameObjects
	);


private:
	GraphicsSystemImpl * impl;
};

