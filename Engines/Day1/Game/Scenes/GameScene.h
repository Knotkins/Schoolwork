#ifndef GAMESCENE_H
#define GAMESCENE_H

//#include "../../Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>
#include "../../Engine/Audio/AudioHandler.h"
#include "../../Engine/Core/JsonParser.h"

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	virtual void Draw();
	ParticleEmitter* part;
	//AudioSource music;
	//CREATE AN EMITTER AND USE IT TO RENDER AND UPDATE THE THINGS
private:
};

#endif // !GAMESCENE_H