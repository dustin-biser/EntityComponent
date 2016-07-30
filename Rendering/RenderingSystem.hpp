//
// RenderingSystem.hpp
//
#pragma once


// Forward declare.
class RenderingSystemImpl;


class RenderingSystem {
public:
	// Adjusts Viewport transformation for drawn scene.
	// Arguments given in screen pixels.
	static void setViewport (
		int x, int y,
		int width, int height
	);

	static void renderScene();

private:
	static RenderingSystemImpl * impl;
};
