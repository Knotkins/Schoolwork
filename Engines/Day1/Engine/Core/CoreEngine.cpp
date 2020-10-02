#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false), FPS(120), gameInterface(nullptr), currentSceneNum(0), camera(nullptr) {
}

CoreEngine::~CoreEngine() {
	OnDestroy();
}

CoreEngine* CoreEngine::getInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}

	return engineInstance.get();
}


bool CoreEngine::OnCreate(std::string name_, int width_, int height_) {
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);
	
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::fatalError("Window failed to initialize", "CoreEngine.cpp", __LINE__);
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->getWindow(),
		window->getWidth() / 2,
		window->getHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProram("colorShader", "Engine/Shaders/ColorVertexShader.glsl", "Engine/Shaders/ColorFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProram("basicShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");


	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::fatalError("Game Interface failed to initialize", "CoreEngine.cpp", __LINE__);
			return isRunning = false;
		}
	}
	
	timer.Start();

	Debug::Info("Everything was created okay", "CoreEngine.cpp", __LINE__);

	return isRunning = true;
}

void CoreEngine::Run() {
	while (isRunning) {
		timer.UpdateFrameTicks();
		EventListener::Update();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(FPS));
	}

	if (!isRunning) {
		OnDestroy();
	}
}

bool CoreEngine::getIsRunning() const {
	return isRunning;
}

void CoreEngine::OnDestroy() {

	delete gameInterface;
	gameInterface = nullptr;
	
	delete window;
	window = nullptr;

	delete camera;
	camera = nullptr;

	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();

	SDL_Quit();
	exit(0);
}

void CoreEngine::Update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameInterface) {
		gameInterface->Render();
	}
	SDL_GL_SwapWindow(window->getWindow());
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

int CoreEngine::GetCurrentScene() {
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_) {
	currentSceneNum = sceneNum_;
}

void CoreEngine::Exit() {
	isRunning = false;
}

glm::vec2 CoreEngine::GetWindowSize() const {
	return glm::vec2(window->getWidth(), window->getHeight());
}

Camera* CoreEngine::GetCamera() const {
	return camera;
}

void CoreEngine::SetCamera(Camera* camera_) {
	camera = camera_;
}

void CoreEngine::NotifyOfMousePressed(glm::vec2 mouse_) {
}

void CoreEngine::NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_) {
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 mouse_) {
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_) {
	if (camera) {
		camera->ProcessMouseScroll(y_);
	}
}