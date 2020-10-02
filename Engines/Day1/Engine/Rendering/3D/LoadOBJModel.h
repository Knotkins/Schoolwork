#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include "Mesh.h"
#include "../../Core/Debug.h"
#include "../../FX/MaterialLoader.h"
#include "../../Math/BoundingBox.h"
#include <sstream>

class LoadOBJModel {
public:
	LoadOBJModel();
	~LoadOBJModel();

	void LoadModel(const std::string& objFilePath_);
	void LoadModel(const std::string& objFilePath_, const std::string& matFilePath_);
	std::vector<vertex> GetVerts();
	std::vector<int> GetIndices();
	std::vector<SubMesh> GetSubMeshes();

	BoundingBox GetBoundingBox();

	void OnDestroy();

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textCoords;
	std::vector<int> indices;
	std::vector<int> normalIndicies;
	std::vector<int> textIndicies;
	std::vector<vertex> meshVertices;
	std::vector<SubMesh> subMeshes;

	void PostProcessing();
	void LoadMaterial(const std::string& fileName_);
	void LoadMaterialLibrary(const std::string& matFilePath_);

	BoundingBox box;
	Material currentMaterial;
};
#endif // !LOADOBJMODEL_H