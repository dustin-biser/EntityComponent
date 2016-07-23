//
// GraphicsSystem.cpp
//
#include "GraphicsSystem.hpp"
#include "Mesh2d.hpp"
#include "GraphicsComponent.hpp"
#include "GameObject.hpp"
#include "graphics.h"

#include <cmath>

#define MAX_LINES_DRAWN 1024


static inline TransformComponent multiplyTransforms(
	const TransformComponent & tA,
	const TransformComponent & tB
);

static inline Vertex transformVertex (
	const Vertex & vertex,
	const TransformComponent & transform
);


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

	void buildLinesFromGameObject (
		const GameObject & gameObject,
		std::vector<Line> & lineList,
		size_t & currentLine,
		const TransformComponent & parentTransform = TransformComponent()
	);

	void drawScene (
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
void GraphicsSystem::drawScene (
	GameObject * gameObjects,
	size_t numGameObjects
) {
	impl->drawScene(gameObjects, numGameObjects);
}

//---------------------------------------------------------------------------------------
void GraphicsSystemImpl::drawScene (
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
	const TransformComponent & parentTransform
) {
	TransformComponent transform = multiplyTransforms(gameObject.transform, parentTransform);
	const Mesh2d * mesh = gameObject.graphics->mesh;
	const auto vertexList = mesh->vertexList;

	for (size_t index(0); index < mesh->edgeIndexList.size(); index += 2) {
		const Index indexV0 = mesh->edgeIndexList[index];
		const Index indexV1 = mesh->edgeIndexList[index+1];
		Vertex v0 = transformVertex(vertexList[indexV0], transform);
		Vertex v1 = transformVertex(vertexList[indexV1], transform);

		lineList[numLines] = Line {v0, v1, gameObject.graphics->color};
		++numLines;
	}

	// Build lines from child gameObjects.
	for (const auto child : gameObject.childObjects) {
		buildLinesFromGameObject(*child, lineList, numLines, gameObject.transform);
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

//---------------------------------------------------------------------------------------
static inline TransformComponent multiplyTransforms (
	const TransformComponent & tA,
	const TransformComponent & tB
) {
	TransformComponent result;
	result.position = tA.position + tB.position;
	result.scale = tA.scale * tB.scale;
	result.rotationAngle = tA.rotationAngle + tB.rotationAngle;

	return result;
}

//---------------------------------------------------------------------------------------
static inline Vertex transformVertex (
	const Vertex & vertex,
	const TransformComponent & transform
) {
	float x = vertex.x;
	float y = vertex.y;

	// Scale
	x = x * transform.scale.x;
	y = y * transform.scale.y;

	// Rotate
	const float angle = transform.rotationAngle;
	const float sinAngle = std::sin(angle);
	const float cosAngle = std::cos(angle);
	x = cosAngle * x - sinAngle * y;
	y = sinAngle * x + cosAngle * y;

	// Translate
	x += transform.position.x;
	y += transform.position.y;

	return Vertex {x, y};
}
