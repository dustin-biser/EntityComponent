//
// Mesh2d.hpp
//
#pragma once

#include <vector>
#include <string>
#include "vec2.hpp"

typedef vec2 Vertex;
typedef unsigned char Index;
typedef std::string MeshId;

struct Mesh2d {
	MeshId meshId;
	std::vector<Vertex> vertexList;
	std::vector<Index> edgeIndexList;
};
