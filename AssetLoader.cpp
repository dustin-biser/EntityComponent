//
// AssetLoader.cpp
//
#include "AssetLoader.hpp"
#include "Mesh2d.hpp"

#include <sstream>
using std::istringstream;

#include <unordered_map>
using std::unordered_map;

//---------------------------------------------------------------------------------------
void AssetLoader::decodeMesh (
	const char * const assetDefinition,
	Mesh2d & mesh
) {
	std::istringstream inputStream(assetDefinition);
	std::string currentLine;

	size_t numIds(0);
	Mesh2d * currentMesh = &mesh;

	// Hash-map for going from MeshId to Mesh2d.
	std::unordered_map<MeshId, Mesh2d *> meshIdMap;

	while (!inputStream.eof()) {
		getline(inputStream, currentLine);

		if (currentLine.length() < 4) {
			// Empty or invalid line, so skip.
			continue;
		} 
		else if (currentLine.compare(0, 2, "id") == 0) {
			++numIds;

			// Get MeshId
			std::istringstream inStream(currentLine.substr(3));
			MeshId meshId;
			inStream >> std::skipws >> meshId;

			// Store address of mesh in meshIdMap.
			meshIdMap[meshId] = &mesh;

			if (numIds == 1) {
				currentMesh->meshId = std::move(meshId);
			}
			else {
				// Is a child mesh
				getline(inputStream, currentLine);
				if (currentLine.compare(0, 6, "parent") == 0) {
					// Get parent MeshId
					std::istringstream inStream(currentLine.substr(7));
					MeshId parentMeshId;
					inStream >> std::skipws >> parentMeshId;

					// Get Parent Mesh
					Mesh2d * pMesh = meshIdMap.at(parentMeshId);

					// Construct new subMesh and add it to parent
					Mesh2d childMesh;
					childMesh.meshId = std::move(meshId);
					pMesh->subMeshes.push_back(childMesh);

					currentMesh = &pMesh->subMeshes.back();
				}
			}
		}
		else if (currentLine.compare(0, 4, "vert") == 0) {
			// Read vertex (x,y).
			std::istringstream inStream(currentLine.substr(5));
			float x;
			float y;
			inStream >> std::skipws >> x;
			inStream >> std::skipws >> y;

			currentMesh->vertexList.push_back(Vertex(x, y));
		}
		else if (currentLine.compare(0, 4, "edge") == 0) {
			// Read edge index (start, end)
			std::istringstream inStream(currentLine.substr(5));
			Index edgeStart;
			Index edgeEnd;
			inStream >> std::skipws >> edgeStart;
			inStream >> std::skipws >> edgeEnd;

			currentMesh->edgeIndexList.push_back(edgeStart);
			currentMesh->edgeIndexList.push_back(edgeEnd);
		}
	}
}

