#include "TestComponent.h"
#include <iostream>
TestComponent::~TestComponent()
{
}

void Component::OnCreate(GameObject* parent){
	std::cout << "Attached Test component to game object!" << std::endl;
}

void Component::Update(float deltaTime) {
	std::cout << "Test component update called!" << std::endl;
}