#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H
#include "Component.h"
class TestComponent : public Component
{
public:
	TestComponent();
	virtual ~TestComponent();
	virtual void OnCreate(GameObject* parent_);
	virtual void Update(float deltaTime);

};

#endif // !TESTCOMPONENT_H