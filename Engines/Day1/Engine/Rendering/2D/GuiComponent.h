#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H
#include <glm/glm.hpp>
class Camera;


class GuiComponent
{
public:
	GuiComponent();
	virtual ~GuiComponent();
	virtual void Draw(Camera* camera_, glm::vec2 parentPosition_) = 0;
	virtual void FindContainingPoint() = 0;
};

#endif // !GUICOMPONENT_H