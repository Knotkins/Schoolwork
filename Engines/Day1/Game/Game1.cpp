#include "Game1.h"

Game1::Game1() : GameInterface(), currentScene(nullptr), currentSceneNum(0){
}

Game1::~Game1() {
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate() {

	ShaderHandler::GetInstance()->CreateProram("colorShader", "Engine/Shaders/ColorVertexShader.glsl", "Engine/Shaders/ColorFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProram("basicShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProram("spriteShader", "Engine/Shaders/SpriteVertShader.glsl", "Engine/Shaders/SpriteFragShader.glsl");
	ShaderHandler::GetInstance()->CreateProram("particleShader", "Engine/Shaders/ParticleVertShader.glsl", "Engine/Shaders/ParticleFragShader.glsl");

	if (CoreEngine::getInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		if (!currentScene->OnCreate()) {
			Debug::fatalError("Scene failed to create", "Game1.cpp", __LINE__);
			return false;
		}
		return true;
	}
	Debug::fatalError("Engine scene number is not zero", "Game1.cpp", __LINE__);
	return false;
}

void Game1::Update(const float deltaTime_) {
	if (currentSceneNum != CoreEngine::getInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentScene->Render();
	Draw();
	SDL_GL_SwapWindow(CoreEngine::getInstance()->getWindow()->getWindow());

}

void Game1::Draw()
{
	currentScene->Draw();
}

void Game1::BuildScene() {
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::getInstance()->GetCurrentScene()) {
		case 1:
			currentScene = new GameScene();
			break;
		default:
			currentScene = new StartScene();
			break;
	}

	if (!currentScene->OnCreate()) {
		Debug::fatalError("Scene failed to create", "Game1.cpp", __LINE__);
		CoreEngine::getInstance()->Exit();
	}
	currentSceneNum = CoreEngine::getInstance()->GetCurrentScene();
}