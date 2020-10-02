#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : currentMaterial(Material()) {
	vertices.reserve(200);
	normals.reserve(200);
	textCoords.reserve(200);
	indices.reserve(200);
	normalIndicies.reserve(200);
	textIndicies.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel() {
	OnDestroy();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_) {
	std::ifstream in(objFilePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + objFilePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	double maxX, minX, maxY, minY, maxZ, minZ;
	bool firstRunThrough = true;
	while (std::getline(in, line)) {
		
		if (line.substr(0, 2) == "v ") {
			std::istringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			if (firstRunThrough)
			{
				maxX = minX = x;
				maxY = minY = y;
				maxZ = minZ = z;
				firstRunThrough = false;
			}
			if (x > maxX)
			{
				maxX = x;
			}
			else if (x < minX)
			{
				minX = x;
			}
			if (y > maxY)
			{
				maxY = y;
			}
			else if (y < minY)
			{
				minY = y;
			}
			if (z > maxZ)
			{
				maxZ = z;
			}
			else if (z < minZ)
			{
				minZ = z;
			}
			vertices.push_back(glm::vec3(x, y, z));
		}
		
		else if (line.substr(0, 3) == "vn ") {
			std::istringstream vn(line.substr(3));
			GLfloat n1, n2, n3;
			vn >> n1 >> n2 >> n3;
			normals.push_back(glm::vec3(n1, n2, n3));
		}

		else if (line.substr(0, 3) == "vt ") {
			std::istringstream vt(line.substr(3));
			float x, y;
			vt >> x >> y;
			textCoords.push_back(glm::vec2(x, y));
		}

		else if (line.substr(0, 2) == "f ") {
			std::istringstream f(line.substr(2));
			int x, y, z;
			std::string faces;
			char slash;
			for (int i = 0; i < 3; i++) {
				f >> x >> slash >> y >> slash >> z;

				indices.push_back(x - 1);
				textIndicies.push_back(y - 1);
				normalIndicies.push_back(z - 1);
			}
		}

		/*if (line.substr(0, 3) == "vn ") {
			std::istringstream vn(line.substr(3));
			GLfloat n1, n2, n3;
			vn >> n1 >> n2 >> n3;
			normals.push_back(glm::vec3(n1, n2, n3));
		}
		if (line.substr(0, 3) == "vt ") {
			std::istringstream vt(line.substr(3));
			float x, y;
			vt >> x >> y;
			textCoords.push_back(glm::vec2(x, y));
		}
		if (line.substr(0, 2) == "f ") {
			std::istringstream f(line.substr(2));
			int x[3], y[3], z[3];
			std::string faces;
			int i = 0;
			char slash;
			while (f >> faces)
			{
				std::istringstream g(faces);
				g >> x[i] >> slash >> y[i] >> slash >> z[i];
				i++;
			}
			indices.push_back(x[0]);
			indices.push_back(x[1]);
			indices.push_back(x[2]);

			textIndicies.push_back(y[0]);
			textIndicies.push_back(y[1]);
			textIndicies.push_back(y[2]);

			normalIndicies.push_back(z[0]);
			normalIndicies.push_back(z[1]);
			normalIndicies.push_back(z[2]);
		}*/

		/*if (line.substr(0, 2) == "f ") {
			std::string data = line.substr(2);
			int currentEndPos = 0;
			while ((currentEndPos = data.find(' ')) != std::string::npos) {
				std::string chunk = data.substr(0, currentEndPos);
				int subEndPos = 0;

				for (int i = 0; i < 3; i++) {
					int pushBack = 0;
					if ((subEndPos = chunk.find('/')) != std::string::npos) {

						pushBack = std::stoi(chunk.substr(0, subEndPos));

						chunk.erase(0, subEndPos + 1);
					}
					else {
						pushBack = std::stoi(chunk);
					}

					pushBack--;

					switch (i) {
					default:
					case 0:
						indices.push_back(pushBack);
						break;
					case 1:
						textIndicies.push_back(pushBack);
						break;
					case 2:
						normalIndicies.push_back(pushBack);
						break;
					}
				}

				data.erase(0, currentEndPos + 1);
			}
		}*/

		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	box.maxVert = glm::vec3(maxX, maxY, maxZ);
	box.minVert = glm::vec3(minX, minY, minZ);
	PostProcessing();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& matFilePath_) {
	LoadMaterialLibrary(matFilePath_);
	LoadModel(objFilePath_);
}

std::vector<vertex> LoadOBJModel::GetVerts() {
	return meshVertices;
}

std::vector<int> LoadOBJModel::GetIndices() {
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes() {
	return subMeshes;
}

void LoadOBJModel::OnDestroy() {
	vertices.clear();
	normals.clear();
	textCoords.clear();
	indices.clear();
	normalIndicies.clear();
	textIndicies.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::PostProcessing() {
	for (int i = 0; i < indices.size(); i++) {
		vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndicies[i]];
		vert.texCoords = textCoords[textIndicies[i]];
		meshVertices.push_back(vert);
	}

	SubMesh subMesh;
	subMesh.vertexList = meshVertices;
	subMesh.meshIndices = indices;
	subMesh.material = currentMaterial;
	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndicies.clear();
	textIndicies.clear();
	meshVertices.clear();
	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& fileName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& FilePath_) {
	MaterialLoader::LoadMaterial(FilePath_);
}

BoundingBox LoadOBJModel::GetBoundingBox() {
	return box;
}