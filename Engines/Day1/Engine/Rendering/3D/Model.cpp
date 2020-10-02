#include "Model.h"

Model::Model(const std::string objFilePath_, const std::string& matFilePath_, GLuint shaderProgram_) : subMeshes(std::vector<Mesh*>()), shaderProgram(0), modelInstance(std::vector<glm::mat4>()), obj(nullptr) {
	subMeshes.reserve(10);
	shaderProgram = shaderProgram_;
	modelInstance.reserve(5);
	obj = new LoadOBJModel();
	obj->LoadModel(objFilePath_, matFilePath_);
	this->LoadModel();
}

Model::~Model() {
	if (subMeshes.size() > 0) {
		for (auto m : subMeshes) {
			delete m;
			m = nullptr;
		}
		subMeshes.clear();
	}
}

void Model::Render(Camera* camera_) {
	for (auto m : subMeshes) {
		m->Render(camera_, modelInstance);
	}
}

void Model::AddMesh(Mesh* mesh_) {
	subMeshes.push_back(mesh_);
}

glm::mat4 Model::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const {
	glm::mat4 model;

	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);

	return model;
}

int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {
	modelInstance.push_back(GetTransform(position_, angle_, rotation_, scale_));
	return modelInstance.size() - 1;
}

void Model::UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {
	modelInstance[index_] = GetTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(int index_) const {
	return modelInstance[index_];
}

void Model::LoadModel() {
	for (int i = 0; i < obj->GetSubMeshes().size(); i++) {
		subMeshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}

	box = obj->GetBoundingBox();

	delete obj;
	obj = nullptr;
}

glm::vec3 Model::GetPosition() const {
	return position;
}

float Model::GetAngle() const {
	return angle;
}

glm::vec3 Model::GetRotation() const {
	return rotation;
}

glm::vec3 Model::GetScale() const {
	return scale;
}

void Model::SetPosition(glm::vec3 position_) {
	position = position_;
}

void Model::SetAngle(float angle_) {
	angle = angle_;
}

void Model::SetRotation(glm::vec3 rotation_) {
	rotation = rotation_;
}

void Model::SetScale(glm::vec3 scale_) {
	scale = scale_;
}

BoundingBox Model::GetBoundingBox() {
	return box;
}

GLuint Model::GetShaderProgram() const {
	return shaderProgram;
}