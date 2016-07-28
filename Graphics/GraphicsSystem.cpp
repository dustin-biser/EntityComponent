//
// GraphicsSystem.cpp
//
#if false

#include "GraphicsSystem.hpp"
#include "Rendering.hpp"
#include "GameObject.hpp"
#include "ComponentPool.hpp"
#include "graphics.h"
#include "Transform.hpp"

#include <cmath>

#define MAX_LINES_DRAWN 1024


class GraphicsSystemImpl {
private:
	friend class GraphicsSystem;
	GraphicsSystemImpl();

	struct Line {
		Vertex start;
		Vertex end;
		Color color;
	};
	std::vector<Line> lineList;

	// Transforms vertices in world space to window space.
	Transform viewportTransform;


	void buildLinesFromGameObject (
		const GameObject & gameObject,
		std::vector<Line> & lineList,
		size_t & currentLine,
		const Transform & parentTransform = Transform()
	);

	void drawGameObjects (
		GameObject * gameObjects,
		size_t numGameObjects
	);

	void drawLine(const Line & line);
};

//---------------------------------------------------------------------------------------
GraphicsSystemImpl::GraphicsSystemImpl()
	: lineList(MAX_LINES_DRAWN)
{

}

//---------------------------------------------------------------------------------------
GraphicsSystem::GraphicsSystem()
	: impl(new GraphicsSystemImpl())
{

}

//---------------------------------------------------------------------------------------
GraphicsSystem::~GraphicsSystem()
{
	delete impl;
	impl = nullptr;
}

//---------------------------------------------------------------------------------------
void GraphicsSystem::setViewport (
	int x, int y,
	int width, int height
) {
	Transform & viewportTransform = impl->viewportTransform;
	const float half_width = width / 2.0f;
	const float half_height = height / 2.0f;
	viewportTransform.position.x = x + half_width;
	viewportTransform.position.y = y + half_height;
	viewportTransform.scale = vec2(half_width, -half_height);
}

//---------------------------------------------------------------------------------------
void GraphicsSystem::drawGameObjects (
	GameObject * gameObjects,
	size_t numGameObjects
) {
	impl->drawGameObjects(gameObjects, numGameObjects);
}

//---------------------------------------------------------------------------------------
void GraphicsSystem::clearScreen (
	int screenWidth,
	int screenHeight
) const {
	FillRect(0, 0, screenWidth, screenHeight, 0);
}

//---------------------------------------------------------------------------------------
void GraphicsSystemImpl::drawGameObjects (
	GameObject * gameObjects,
	size_t numGameObjects
) {
	size_t numLines(0);

	// Build all wireframe lines from all GameObjects and store in lineList.
	for (size_t i(0); i < numGameObjects; ++i) {
		buildLinesFromGameObject(gameObjects[i], lineList, numLines);
	}

	// Batch render all lines in lineList.
	for (size_t i(0); i < numLines; ++i) {
		drawLine(lineList[i]);
	}
}

//---------------------------------------------------------------------------------------
void GraphicsSystemImpl::buildLinesFromGameObject (
	const GameObject & gameObject,
	std::vector<Line> & lineList,
	size_t & numLines,
	const Transform & parentTransform
) {
	Transform transform = gameObject.transform * parentTransform;
	const Mesh2d * mesh = gameObject.graphics->mesh;
	const auto vertexList = mesh->vertexList;

	for (size_t index(0); index < mesh->edgeIndexList.size(); index += 2) {
		const Index indexV0 = mesh->edgeIndexList[index];
		const Index indexV1 = mesh->edgeIndexList[index+1];

		// Transform vertices from model space to world space.
		Vertex v0 = transform * vertexList[indexV0];
		Vertex v1 = transform * vertexList[indexV1];

		// Transform vertices to window coordinate space.
		v0 = viewportTransform * v0;
		v1 = viewportTransform * v1;

		lineList[numLines] = Line {v0, v1, gameObject.graphics->color};
		++numLines;
	}

	// Build lines from child gameObjects.
	for (auto & child : gameObject.childObjects) {
		GameObject * childGameObject = child.residentPool->getObject(child.id);
		buildLinesFromGameObject(*childGameObject, lineList, numLines, gameObject.transform);
	}
}

//---------------------------------------------------------------------------------------
void GraphicsSystemImpl::drawLine(const Line & line)
{
	const Color & color = line.color;
	const unsigned int red = static_cast<unsigned int>(color.red * 255.0f);
	const unsigned int blue = static_cast<unsigned int>(color.blue * 255.0f);
	const unsigned int green = static_cast<unsigned int>(color.green * 255.0f);

	DrawLine (
		static_cast<int>(line.start.x),
		static_cast<int>(line.start.y),
		static_cast<int>(line.end.x), 
		static_cast<int>(line.end.y),
		GetRGB(red, green, blue)
	);
}
#endif
