#include "TestComponent.h"
#include <iostream>
TestComponent::TestComponent()
{
}
TestComponent::~TestComponent()
{
}

void TestComponent::OnCreate(GameObject* parent){
	std::cout << "Attached Test component to game object!" << std::endl;
}

void TestComponent::Update(float deltaTime) {
	std::cout << "Test component update called!" << std::endl;
}