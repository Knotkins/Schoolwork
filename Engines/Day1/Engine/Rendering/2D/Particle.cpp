#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_) : VAO(0), shaderProgram(0), modelLoc(0), viewLoc(0), projLoc(0), colourLoc(0)
{
	Vertex2D a, b, c, d;
	a.position = (glm::vec2(-0.5, 0.5)); a.textureCoords = (glm::vec2(0.0, 0.0));
	b.position = (glm::vec2(0.5, 0.5)); b.textureCoords = (glm::vec2(1.0, 0.0));
	c.position = (glm::vec2(-0.5, -0.5)); c.textureCoords = (glm::vec2(0.0, 1.0));
	d.position = (glm::vec2(0.5, -0.5)); d.textureCoords = (glm::vec2(1.0, 1.0));
	vertexlist.push_back(a);
	vertexlist.push_back(b);
	vertexlist.push_back(c);
	vertexlist.push_back(d);


	lifeTime = 10.0;

	shaderProgram = ShaderHandler::GetInstance()->GetShader("particleShader");
	GenerateBuffers();
}

Particle::~Particle()
{
	glDeleteVertexArrays(1, &VAO);
}

void Particle::Render(Camera* camera_)
{

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glm::mat4 transformMat;

	transformMat = glm::translate(transformMat, position);
	//transformMat = glm::rotate(transformMat, angle, glm::vec3(0.0, 0.0, 1.0));
	transformMat = glm::scale(transformMat, glm::vec3(size, size, size));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformMat)); //might need model matrix
	glUniform4fv(colourLoc, 1, glm::value_ptr(colour));

	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_PROGRAM_POINT_SIZE);
	glBindVertexArray(VAO);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDrawArrays(GL_POINTS, 0, 1); //remember to set the value of gl_PointSize in the vertex shader
	glDisable(GL_PROGRAM_POINT_SIZE);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Particle::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, vertexlist.size() * sizeof(Vertex2D), &vertexlist[0], GL_STATIC_DRAW);

	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	colourLoc = glGetUniformLocation(shaderProgram, "colour");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
}
