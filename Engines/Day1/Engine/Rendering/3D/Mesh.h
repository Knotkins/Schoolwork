#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

struct vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;

	glm::vec2 texCoords;
};

struct SubMesh {
	std::vector<vertex> vertexList;
	std::vector<int> meshIndices;
	Material material;
};

class Mesh {
public:
	Mesh() {};
	~Mesh() {};
	
	virtual void Render(Camera* camera_,std::vector<glm::mat4> instances_) = 0;
private:
	//virtual void generateBuffers() = 0;
};

#endif // !MESH_H