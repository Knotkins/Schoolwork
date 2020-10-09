#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/CoreEngine.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

class Game1 : public GameInterface {
public:
	Game1();
	virtual ~Game1();
	
	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	virtual void Draw();

private:
	Scene* currentScene;

	int currentSceneNum;

	void BuildScene();
};

#endif // !GAME1_H