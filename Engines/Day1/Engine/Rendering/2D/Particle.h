#ifndef PARTICLE_H
#define PARTICLE_H
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics/TextureHandler.h"
#include "../../Graphics/ShaderHandler.h"
#include "../2D/SpriteSurface.h"
//struct Vertex2D {
//	glm::vec2 position;
//	glm::vec2 textureCoords;
//};
class Particle
{
public:
	Particle(GLuint shaderProgram_, GLuint textureID_ = 0);
	~Particle();

	void Render(Camera* camera_);

	glm::vec3 position;
	glm::vec3 velocity;
	float lifeTime;
	glm::vec3 colour;
	float size;
private:
	void GenerateBuffers();
	std::vector<Vertex2D> vertexlist;

	GLuint VAO;
	GLuint modelLoc, viewLoc, projLoc;
	GLuint textureID;
	GLuint viewPositionLoc;
	GLuint colourLoc;
	GLuint shaderProgram;
	GLuint textureLoc;
};

#endif // !PARTICLE_H
