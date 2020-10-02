#ifndef COMPONENT_H
#define COMPONENT_H
class GameObject;

class Component
{
public:
	Component();
	~Component();
	void OnCreate(GameObject* parent_);
	void Update(float deltaTime);

protected:
	GameObject* parent;
};
#endif // !COMPONENT_H
