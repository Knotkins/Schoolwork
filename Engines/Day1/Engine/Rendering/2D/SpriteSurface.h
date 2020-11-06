#ifndef SPRITESURFACE_H
#define SPRITESURFACE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "../../Camera/Camera.h"
#include "../../Graphics/TextureHandler.h"
#include "../../Graphics/ShaderHandler.h"


struct Vertex2D {
	glm::vec2 position;
	glm::vec2 textureCoords;
};
class SpriteSurface
{
public:
	SpriteSurface(std::string name_, float scale_, float angle_, glm::vec4 tint_);
	~SpriteSurface();

	void Draw(Camera* camera_, glm::vec2 position_);
	float GetWidth();
	float GetHieght();

	glm::vec4 tint;

private:
	void generateBuffers();


	GLuint VAO, VBO;
	GLuint modelLoc, viewLoc, projLoc;
	GLuint textureID;
	GLuint viewPositionLoc;
	GLuint tintLoc;
	GLuint shaderProgram;
	GLuint textureLoc;


	std::vector<Vertex2D> vertexlist;

	std::string name;
	float scale;
	float angle;
	float width;
	float hieght;
};

#endif // !SPRITESURFACE_H