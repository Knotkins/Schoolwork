#ifndef OPENGLMESH_H
#define OPENGLMESH_H
#include "Mesh.h"
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
class OpenGLMesh : public Mesh
{
public:
	OpenGLMesh(SubMesh subMesh_, GLuint shaderProgram_);
	~OpenGLMesh();

	virtual void Render(Camera* camera_, std::vector<glm::mat4> instances_);

private:
	virtual void generateBuffers();

	GLuint VAO, VBO;

	std::vector<vertex> vertexlist;

	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc;
	GLuint textureID;
	GLuint viewPositionLoc, lightPositionLoc, ambientLightLoc, diffuseLightLoc, lightColorLoc;
	GLuint diffuseMapLoc, ambientMatLoc, diffuseMatLoc, specularMatLoc, shininessLoc, transparencyLoc;
};

#endif // !OPENGLMESH_H
