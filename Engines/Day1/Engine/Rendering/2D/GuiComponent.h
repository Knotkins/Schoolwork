#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

class GuiComponent
{
public:
	GuiComponent();
	virtual ~GuiComponent();
	virtual void Draw();
	virtual void FindContainingPoint();
};

#endif // !GUICOMPONENT_H