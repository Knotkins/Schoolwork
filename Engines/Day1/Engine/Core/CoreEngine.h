#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"
#include "../Rendering/3D/GameObject.h"
#include "../Graphics/ShaderHandler.h"
#include "../Camera/Camera.h"
#include "../Graphics/TextureHandler.h"
#include "../Events/EventListener.h"
#include "../Rendering/SceneGraph.h"
#include "Renderer.h"
#include "OpenGLRenderer.h"

class CoreEngine
{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;

	CoreEngine& operator = (const CoreEngine&) = delete;
	CoreEngine& operator = (const CoreEngine&&) = delete;

	bool OnCreate(std::string name_, int width_, int height_);
	bool getIsRunning() const;

	void Run();
	void SetGameInterface(GameInterface* gameInterface_, RenderType renderType_ = RenderType::TYPE_OPENGL);
	void SetCurrentScene(int sceneNum_);
	void Exit();

	static CoreEngine* getInstance();

	int GetCurrentScene();

	Camera* GetCamera() const;

	void SetCamera(Camera* camera_);

	glm::vec2 GetWindowSize() const;

	void NotifyOfMousePressed(glm::vec2 mouse_);
	void NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_);
	void NotifyOfMouseMove(glm::vec2 mouse_);
	void NotifyOfMouseScroll(int y_);

	RenderType GetRenderType();
	Renderer* GetRenderer();

	void CreateRenderer();

	Window* getWindow() const;

private:
	CoreEngine();
	~CoreEngine();

	static std::unique_ptr<CoreEngine> engineInstance;

	friend std::default_delete<CoreEngine>;

	void OnDestroy();
	void Update(const float deltaTime_);
	void Render();
	
	Window* window;
	GameInterface* gameInterface;
	
	bool isRunning;

	Timer timer;

	unsigned int FPS;

	int currentSceneNum;

	Camera* camera;

	RenderType renderType;
	Renderer* renderer;
};
#endif // !COREENGINE_H