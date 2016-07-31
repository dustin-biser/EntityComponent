//
// MeshDirectory.hpp
//
#pragma once

#include "Assets/Mesh2d.hpp"

// Forward declare.
class MeshDirectoryImpl;


// Class for locating pre-defined Mesh2d assets.
class MeshDirectory {
public:
	static Mesh2d * getMesh(const MeshID & meshId);

private:
	static MeshDirectoryImpl * impl;
};