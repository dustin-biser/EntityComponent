//
// AssetLoader.hpp
//
#pragma once

// Forward declare
struct Mesh2d;

class AssetLoader {
public:

	static void decodeMesh (
		const char * const assetDefinition,
		Mesh2d & mesh
	);
};