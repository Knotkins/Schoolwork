#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "Renderer.h"

class Window {
public:
	Window();
	~Window();
	
	bool OnCreate(std::string name_, int width_, int height_);

	void OnDestroy();
	
	int getWidth();
	int getHeight();

	SDL_Window* getWindow() const;

private:
	Renderer* renderer;
	
	int width;
	int height;

	SDL_Window* window;

};
#endif // !WINDOW_H