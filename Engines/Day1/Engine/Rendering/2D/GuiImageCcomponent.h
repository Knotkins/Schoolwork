#ifndef GUIIMAGECOMPONENT_H
#define GUIIMAGECOMPONENT_H
#include "GuiComponent.h"
#include <string>
#include <glm/glm.hpp>
#include "../../Camera/Camera.h"
#include "SpriteSurface.h"

class GuiImageCcomponent : public GuiComponent
{
public:
	GuiImageCcomponent();
	virtual ~GuiImageCcomponent();

	virtual void OnCreate(std::string name_, glm::vec2 offset_, float scale_, float angle, glm::vec4 tint_);
	virtual void Draw(Camera* camera_, glm::vec2 parentPosition_);
	virtual void FindContainingPoint();

private:
	SpriteSurface* spriteSurface;
	glm::vec2 offset;
};

#endif // !GUIIMAGECOMPONENT_H
