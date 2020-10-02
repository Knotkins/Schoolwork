#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), modelLoc(0), viewLoc(0), projLoc(0) {
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	generateBuffers();
}

Mesh::~Mesh() {
	subMesh.vertexList.clear();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_) {

	//	In the Render function use the camera to send the uniform’s information

	glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glUniform3f(viewPositionLoc,
		camera_->GetPosition().x,
		camera_->GetPosition().y,
		camera_->GetPosition().z);

	glUniform3f(lightPositionLoc,
		camera_->GetLightSource()[0]->GetPosition().x,
		camera_->GetLightSource()[0]->GetPosition().y,
		camera_->GetLightSource()[0]->GetPosition().z);

	glUniform1f(ambientLightLoc,
		camera_->GetLightSource()[0]->GetAmbientValue());

	glUniform1f(diffuseLightLoc,
		camera_->GetLightSource()[0]->GetDiffuseValue());

	glUniform3f(lightColorLoc,
		camera_->GetLightSource()[0]->GetLightColor().x,
		camera_->GetLightSource()[0]->GetLightColor().y,
		camera_->GetLightSource()[0]->GetLightColor().z);

	glUniform3f(ambientMatLoc,
		subMesh.material.ambient.x,
		subMesh.material.ambient.y,
		subMesh.material.ambient.z);

	glUniform3f(diffuseMatLoc,
		subMesh.material.diffuse.x,
		subMesh.material.diffuse.y,
		subMesh.material.diffuse.z);

	glUniform3f(specularMatLoc,
		subMesh.material.specular.x,
		subMesh.material.specular.y,
		subMesh.material.specular.z);

	glUniform1f(shininessLoc,
		subMesh.material.shininess);

	glUniform1f(transparencyLoc,
		subMesh.material.transparency);
		

	glBindVertexArray(VAO);

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::generateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));

	//TEXTURE COORDINATES
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, texCoords));

	//COLOR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, color));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	viewPositionLoc = glGetUniformLocation(shaderProgram, "cameraPosition");

	lightPositionLoc = glGetUniformLocation(shaderProgram, "light.lightPosition");
	ambientLightLoc = glGetUniformLocation(shaderProgram, "light.ambientValue");
	diffuseLightLoc = glGetUniformLocation(shaderProgram, "light.diffuseValue");
	lightColorLoc = glGetUniformLocation(shaderProgram, "light.lightColor");

	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	ambientMatLoc = glGetUniformLocation(shaderProgram, "material.ambientMat");
	diffuseMatLoc = glGetUniformLocation(shaderProgram, "material.diffuseMat");
	specularMatLoc = glGetUniformLocation(shaderProgram, "material.specularMat");
	shininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
}