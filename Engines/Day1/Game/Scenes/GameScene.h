#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>
#include "../../Engine/Rendering/3D/TestComponent.h"
#include "../../Engine/Audio/AudioHandler.h"
#include "../../Engine/Audio/AudioSource.h"

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	virtual void Draw();
	//AudioSource music;

private:
};

#endif // !GAMESCENE_H