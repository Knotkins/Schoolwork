#include "GuiImageCcomponent.h"

GuiImageCcomponent::GuiImageCcomponent()
{
}

GuiImageCcomponent::~GuiImageCcomponent()
{
	delete spriteSurface;
	spriteSurface = nullptr;
}

void GuiImageCcomponent::OnCreate(std::string name_, glm::vec2 offset_ = glm::vec2(0,0), float scale_ = 1.0, float angle_ = 0.0, glm::vec4 tint_ = glm::vec4(1,1,1,1))
{
	offset = offset_;
	spriteSurface = new SpriteSurface(name_, scale_, angle_, tint_);
}

void GuiImageCcomponent::Draw(Camera* camera_, glm::vec2 parentPosition_)
{
}

void GuiImageCcomponent::FindContainingObject()
{
	if (spriteSurface) {

	}
}
