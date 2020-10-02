#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "Component.h"
class GameObject {
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();

	void Render(Camera* camera_);
	void Update(const float deltaTime_);
	void OnDestroy();

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	bool GetHit() const;

	float GetAngle() const;

	std::string GetnameTag() const;

	void SetPosition(glm::vec3 position_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetnameTag(std::string nameTag_);

	void SetAngle(float angle_);
	void SetHit(bool hit_, int buttonType_);

	BoundingBox GetBoundingBox() const;

	template <typename T> void AddComponent(T t_);
	template <typename T> Component GetComponent(T t_);
	template <typename T> void RemoveComponent(T t_);


private:
	Model* model;
	int modelInstance;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float angle;

	BoundingBox box;

	std::string nameTag;

	bool hit;

	std::vector<Component*> components;
};
#endif // !GAMEOBJECT_H


