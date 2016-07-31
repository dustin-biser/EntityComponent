//
// Mesh2d.hpp
//
#pragma once

#include <vector>
#include <string>
#include "vec2.hpp"

typedef vec2 Vertex;
typedef unsigned int Index;
typedef std::string MeshID;

struct Mesh2d {
	MeshID meshId;
	std::vector<Vertex> vertexList;
	std::vector<Index> edgeIndexList;
};
