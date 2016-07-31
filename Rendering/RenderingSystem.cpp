//
// RenderingSystem.cpp
//
#include "RenderingSystem.hpp"

#include <cmath>

#include "Assets/Mesh2d.hpp"

#include "Core/ComponentPoolLocator.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/Transform.hpp"

#include "Config/EngineSettings.hpp"

#include "Rendering/Rendering.hpp"
#include "Rendering/graphics.h"



class RenderingSystemImpl {
private:
	friend class RenderingSystem;
	RenderingSystemImpl();

	struct Line {
		int start_x;
		int start_y;
		int end_x;
		int end_y;
		Color color;
	};

// Methods:
	void buildLinesFromRenderingComponent (
		const Rendering & rendering,
		std::vector<Line> & lineList,
		size_t & numLines,
		const Transform & parentTransform
	);

	void renderScene();

	void drawLine(const Line & line);

	void clearScreen() const;


// Members:
	int m_screenWidth;
	int m_screenHeight;

	std::vector<Line> m_lineList;

	// Transforms vertices from World Space to Window Coordinate Space.
	Transform m_viewportTransform;
};

RenderingSystemImpl * RenderingSystem::impl = new RenderingSystemImpl();


//---------------------------------------------------------------------------------------
RenderingSystemImpl::RenderingSystemImpl()
	: m_lineList(EngineSettings::MAX_LINES_RENDERED_PER_FRAME)
{

}

//---------------------------------------------------------------------------------------
void RenderingSystem::setViewport (
	int x, int y,
	int width, int height
) {
	Transform & viewportTransform = impl->m_viewportTransform;
	const float half_width = width * 0.5f;
	const float half_height = height * 0.5f;
	viewportTransform.position.x = x + half_width;
	viewportTransform.position.y = y + half_height;
	viewportTransform.scale = vec2(half_width, -half_height);
	viewportTransform.rotationAngle = 0.0f;

	impl->m_screenWidth = width;
	impl->m_screenHeight = height;
}

//---------------------------------------------------------------------------------------
void RenderingSystem::renderScene()
{
	impl->clearScreen();
	impl->renderScene();
}

//---------------------------------------------------------------------------------------
void RenderingSystemImpl::clearScreen (
) const {
	FillRect(0, 0, m_screenWidth, m_screenHeight, 0);
}

//---------------------------------------------------------------------------------------
void RenderingSystemImpl::renderScene()
{
	size_t numLines(0);

	ComponentPool<Rendering> * renderingPool = ComponentPoolLocator<Rendering>::getPool();
	Rendering * rendering = renderingPool->beginActive();

	// Build wire-frame lines from all Rendering components and store in lineList.
	for (size_t i(0); i < renderingPool->numActive(); ++i) {
		Transform transform = rendering[i].transform();

		//-- Apply hierarchical parent transforms
		Transform * parent = transform.getParent();
		Transform parentTransforms;
		while (parent) {
			parentTransforms = parent->transform() * parentTransforms;
			parent = parent->getParent();
		}
		transform = parentTransforms * transform;

		buildLinesFromRenderingComponent(rendering[i], m_lineList, numLines, transform);
	}

	// Batch render all lines in lineList.
	for (size_t i(0); i < numLines; ++i) {
		drawLine(m_lineList[i]);
	}
}

//---------------------------------------------------------------------------------------
void RenderingSystemImpl::buildLinesFromRenderingComponent (
	const Rendering & rendering,
	std::vector<Line> & lineList,
	size_t & numLines,
	const Transform & transform
) {
	const Mesh2d * mesh = rendering.mesh;
	const auto vertexList = mesh->vertexList;

	for (size_t index(0); index < mesh->edgeIndexList.size(); index += 2) {
		const Index indexV0 = mesh->edgeIndexList[index];
		const Index indexV1 = mesh->edgeIndexList[index+1];

		// Transform vertices from model space to world space.
		Vertex v0 = transform * vertexList[indexV0];
		Vertex v1 = transform * vertexList[indexV1];

		// Transform vertices to window coordinate space.
		v0 = m_viewportTransform * v0;
		v1 = m_viewportTransform * v1;

		lineList[numLines] = Line {
			static_cast<int>(v0.x), 
			static_cast<int>(v0.y), 
			static_cast<int>(v1.x), 
			static_cast<int>(v1.y), 
			rendering.color
		};
		++numLines;
	}
}

//---------------------------------------------------------------------------------------
void RenderingSystemImpl::drawLine(const Line & line)
{
	const Color & color = line.color;
	const unsigned int red = static_cast<unsigned int>(color.red * 255.0f);
	const unsigned int blue = static_cast<unsigned int>(color.blue * 255.0f);
	const unsigned int green = static_cast<unsigned int>(color.green * 255.0f);

	DrawLine(line.start_x, line.start_y, line.end_x, line.end_y, GetRGB(red, green, blue));
}
