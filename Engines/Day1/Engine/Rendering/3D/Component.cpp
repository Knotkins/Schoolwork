#include "Component.h"

Component::Component()
{
	parent = nullptr;
}

Component::~Component()
{
	parent = nullptr;
}

void Component::OnCreate(GameObject* parent_)
{
	parent = parent_;
}

void Component::Update(float deltaTime)
{
}
