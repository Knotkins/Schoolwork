#include "GuiObject.h"

GuiObject::GuiObject(glm::vec2 position_) {
	position = position_;
}

GuiObject::~GuiObject()
{
	for (auto m : components) {
		delete m;
		m = nullptr;
	}
	components.clear();
}

void GuiObject::Draw(Camera* camera_)
{
	for (auto m : components) {
		m->Draw(camera_, position);
	}
}

void GuiObject::SetnameTag(std::string nameTag_)
{
	nameTag = nameTag_;
}
