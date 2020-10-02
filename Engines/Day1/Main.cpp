#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"

int main(int argc, char* argv[]) {
	CoreEngine::getInstance()->SetGameInterface(new Game1);

	if (!CoreEngine::getInstance()->OnCreate("GAME258 Engine", 800, 600)) {
		return 0;
	}

	CoreEngine::getInstance()->Run();

	return 0;
}