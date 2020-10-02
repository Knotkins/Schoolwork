#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer {
public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;

	Timer& operator = (const Timer&) = delete;
	Timer& operator = (const Timer&&) = delete;

	Timer();
	~Timer();

	void Start();
	void UpdateFrameTicks();

	float GetDeltaTime() const;
	float GetCurrentTicks();

	unsigned int GetSleepTime(unsigned int FPS_) const;

private:
	unsigned int prevTicks;
	unsigned int currentTicks;

	const float MILLI_TO_SEC = 1000.0f;
};
#endif // !TIMER_H