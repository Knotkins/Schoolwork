#ifndef COMPONENT_H
#define COMPONENT_H
class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();
	virtual void OnCreate(GameObject* parent_);
	virtual void Update(float deltaTime);

protected:
	GameObject* parent;
};
#endif // !COMPONENT_H
