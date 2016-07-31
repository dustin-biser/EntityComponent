//
// MeshDirectory.cpp
//
#include "MeshDirectory.hpp"

#include <unordered_map>
using std::unordered_map;

#include "Assets/AssetLoader.hpp"
#include "Assets/AssetDefinitions.hpp"


class MeshDirectoryImpl {
private:
	friend class MeshDirectory;

	MeshDirectoryImpl();

	std::unordered_map<MeshID, Mesh2d> meshAssetDirectory;
};

MeshDirectoryImpl * MeshDirectory::impl = new MeshDirectoryImpl();


//---------------------------------------------------------------------------------------
MeshDirectoryImpl::MeshDirectoryImpl()
{
	for (auto asset : Asset::assetDefinitions) {
		Mesh2d mesh;
		AssetLoader::decodeMesh(asset, mesh);
		meshAssetDirectory[mesh.meshId] = std::move(mesh);
	}
}


//---------------------------------------------------------------------------------------
Mesh2d * MeshDirectory::getMesh (
	const MeshID & meshId
) {
	return &impl->meshAssetDirectory.at(meshId);
}

