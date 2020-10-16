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

	template <typename T, typename ... Args> void AddComponent(Args&& ... args_)
	{T* newComponent = new T(std::forward<Args>(args_)...);
	if (dynamic_cast<Component*> (newComponent)) {
		if (GetComponent<T>() == nullptr) {
			components.push_back(newComponent);
			newComponent->OnCreate(this);
		}
		else {
			Debug::Error("New component already exists on this object!", __FILE__, __LINE__);
			delete newComponent;
			newComponent = nullptr;
			return;
		}
	}
	else {
		Debug::Error("New component is not of type component!", __FILE__, __LINE__);
		delete newComponent;
		newComponent = nullptr;
		return;
	}
	}
	template <typename T> T* GetComponent()
	{
		for (auto m : components) {
			if (dynamic_cast<T*> (m)) {
				return dynamic_cast<T*> (m);
			}
		}
		return nullptr;
	}

	template <typename T> void RemoveComponent()
	{
		for (int i = 0; i < components.size(); i++) {
			if (dynamic_cast<T*> (components[i])) {
				delete components[i];
				components[i] = nullptr;
				components.erase(components.begin() + i);
				break;
			}
		}

	}


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
