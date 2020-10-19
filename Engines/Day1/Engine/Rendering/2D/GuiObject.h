#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include <glm/glm.hpp>
#include "GuiComponent.h"
#include <vector>
#include <string>
#include "../../Core/Debug.h"
class GuiObject
{
public:
	GuiObject(glm::vec2 position_);
	~GuiObject();

	void Draw();
	void SetnameTag(std::string nameTag_);

	template <typename T> void AddComponent()
	{
		T* newComponent = new T();
		if (dynamic_cast<GuiComponent*> (newComponent)) {
			if (GetComponent<T>() == nullptr) {
				components.push_back(newComponent);
			}
			else {
				Debug::Error("New GUI component already exists on this object!", __FILE__, __LINE__);
				delete newComponent;
				newComponent = nullptr;
				return;
			}
		}
		else {
			Debug::Error("New GUI component is not of type component!", __FILE__, __LINE__);
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
	glm::vec2 position;
	std::vector<GuiComponent*> components;
	std::string nameTag;
};

#endif // !GUIOBJECT_H
