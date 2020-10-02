#include "GameObject.h"

GameObject::GameObject(Model* model_, glm::vec3 position_) : model(nullptr) {
	model = model_;
	position = position_;
	angle = 0.0f;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	scale = glm::vec3(1.0f);
	nameTag = "";
	hit = false;

	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		box = model->GetBoundingBox();
		box.transform = model->GetTransform(modelInstance);
	}
}

GameObject::~GameObject() {
	OnDestroy();
}

void GameObject::Render(Camera* camera_) {
	if (model) {
		model->Render(camera_);
	}
}

void GameObject::OnDestroy() {
	model = nullptr;
}

void GameObject::Update(float deltaTime_) {
		SetAngle(GetAngle() + 0.005f);
}

glm::vec3 GameObject::GetPosition() const {
	return position;
}

glm::vec3 GameObject::GetRotation() const {
	return rotation;
}

glm::vec3 GameObject::GetScale() const {
	return scale;
}

float GameObject::GetAngle() const {
	return angle;
}

std::string GameObject::GetnameTag() const {
	return nameTag;
}

bool GameObject::GetHit() const {
	return hit;
}

void GameObject::SetPosition(glm::vec3 position_) {
	position = position_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_) {
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_) {
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance); 
		box.minVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
		box.maxVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
	}
}

void GameObject::SetAngle(float angle_) {
	angle = angle_; 
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

BoundingBox GameObject::GetBoundingBox() const {
	return box;
}

void GameObject::SetnameTag(std::string nameTag_) {
	nameTag = nameTag_;
}

void GameObject::SetHit(bool hit_, int buttonType_) {
	hit = hit_;
	if (hit) {
		std::cout << nameTag << " was hit" << std::endl;
	}
}