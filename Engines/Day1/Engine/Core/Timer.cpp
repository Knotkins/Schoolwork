#include "Timer.h"

Timer::Timer() : prevTicks(0), currentTicks(0) {
}

Timer::~Timer() {
}

void Timer::Start() {
	prevTicks = SDL_GetTicks();
	currentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks() {
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const {
	return static_cast<float>(currentTicks - prevTicks) / MILLI_TO_SEC;
}

float Timer::GetCurrentTicks() {
	return static_cast<float>(currentTicks) / MILLI_TO_SEC;
}

unsigned int Timer::GetSleepTime(unsigned int FPS_) const {
	unsigned int milliPerFrame = 1000 / FPS_;
	
	if (milliPerFrame == 0) {
		return 0;
	}

	unsigned int sleepTime = milliPerFrame - SDL_GetTicks();

	if (sleepTime > milliPerFrame) {
		return milliPerFrame;
	}
	return sleepTime;
}