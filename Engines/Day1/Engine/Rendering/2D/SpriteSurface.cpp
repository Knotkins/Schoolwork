#include "SpriteSurface.h"

SpriteSurface::SpriteSurface(std::string name_, float scale_, float angle_, glm::vec4 tint_) : VAO(0), VBO(0), shaderProgram(0), scale(1.0), angle(0.0), tint(glm::vec4(1, 1, 1, 1)), modelLoc(0), viewLoc(0), projLoc(0), tintLoc(0)
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

	name = name_;
	scale = scale_;
	angle = angle_;
	tint = tint_;

	if (TextureHandler::GetInstance()->GetTexture(name) == 0) {
		TextureHandler::GetInstance()->CreateTexture(name, "Resources/Textures/" + name + ".png");
	}
	textureID = TextureHandler::GetInstance()->GetTexture(name);
	width = TextureHandler::GetInstance()->GetTextureData(name)->width;
	hieght = TextureHandler::GetInstance()->GetTextureData(name)->height;

	generateBuffers();

}

SpriteSurface::~SpriteSurface()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void SpriteSurface::Draw(Camera* camera_, glm::vec2 position_)
{
	//glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::mat4 transformMat;

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformMat));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));
	glUniformMatrix4fv(tintLoc, 1, GL_FALSE, glm::value_ptr(tint));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexlist.size());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

float SpriteSurface::GetWidth()
{
	return width;
}

float SpriteSurface::GetHieght()
{
	return hieght;
}

void SpriteSurface::generateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertexlist.size() * sizeof(Vertex2D), &vertexlist[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)0);

	//TEXTURE COORDINATES
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, textureCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	viewPositionLoc = glGetUniformLocation(shaderProgram, "cameraPosition");
	tintLoc = glGetUniformLocation(shaderProgram, "tint");
}

