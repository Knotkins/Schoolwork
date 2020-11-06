#include "GameScene.h"

GameScene::GameScene() : Scene() {
}

GameScene::~GameScene() {
}

bool GameScene::OnCreate() {
	Debug::Info("Create Game Scene", "GameScene.cpp", __LINE__);
	
	CoreEngine::getInstance()->SetCamera(new Camera);
	CoreEngine::getInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::getInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f));
	
	AudioHandler::GetInstance()->Initialize(glm::vec3(0.0f, 0.0f, 4.0f));

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	TextureHandler::GetInstance()->CreateTexture("DonaldDuck", "./Resources/Textures/Donald.png");
	TextureHandler::GetInstance()->CreateTexture("particleTest", "./Resources/Textures/Apple_Body.jpg");

	Model* model1 = new Model("./Resources/Models/Dice.obj", "./Resources/Material/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model1);

	Model* model2 = new Model("./Resources/Models/Apple.obj", "./Resources/Material/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model2);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(model1));
	
	std::cout << "Dice Min Vert: " << glm::to_string(model1->GetBoundingBox().minVert) << std::endl;
	std::cout << "Dice Max Vert: " << glm::to_string(model1->GetBoundingBox().maxVert) << std::endl;
	
	std::cout << "Apple Min Vert: " << glm::to_string(model2->GetBoundingBox().minVert) << std::endl;
	std::cout << "Apple Max Vert: " << glm::to_string(model2->GetBoundingBox().maxVert) << std::endl;

	GameObject* apple = new GameObject(model2, glm::vec3 (3.0f, -1.0f, 0.0f));
	apple->SetScale(glm::vec3(0.5f));

	SceneGraph::GetInstance()->AddGameObject(apple, "apple");

	//music = new AudioSource("music.mp3", true, false, true);

	apple->AddComponent<TestComponent>();
	apple->AddComponent<AudioSource>("./Engine/Audio/music.mp3", true, false, true);
	apple->GetComponent<AudioSource>()->PlaySound();
	apple->RemoveComponent<TestComponent>();

	GuiObject* gui = new GuiObject(glm::vec2(0.5,0.5));
	gui->AddComponent<GuiImageCcomponent>();
	gui->GetComponent<GuiImageCcomponent>()->OnCreate("DonaldDuck", glm::vec2(0.0, 0.0), 1.0, 0.0, glm::vec4(1, 1, 1, 1));
	SceneGraph::GetInstance()->AddGuiObject(gui);
	part = new ParticleEmitter(50, "particleTest", "particleShader");
	return true;
}

void GameScene::Update(const float deltaTime_) {
	SceneGraph::GetInstance()->Update(deltaTime_);
	part->Update(deltaTime_);
}

void GameScene::Render() {
	SceneGraph::GetInstance()->Render(CoreEngine::getInstance()->GetCamera());
	part->Render(CoreEngine::getInstance()->GetCamera());
}

void GameScene::Draw()
{
	SceneGraph::GetInstance()->Draw(CoreEngine::getInstance()->GetCamera());
}
