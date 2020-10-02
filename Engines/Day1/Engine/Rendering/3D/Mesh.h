#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include <string>
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
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();
	
	void Render(Camera* camera_,std::vector<glm::mat4> instances_);

private:
	void generateBuffers();

	GLuint VAO, VBO;

	std::vector<vertex> vertexlist;

	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc;
	GLuint textureID;
	GLuint viewPositionLoc, lightPositionLoc, ambientLightLoc, diffuseLightLoc, lightColorLoc;
	GLuint diffuseMapLoc, ambientMatLoc, diffuseMatLoc, specularMatLoc, shininessLoc, transparencyLoc;
};

#endif // !MESH_H