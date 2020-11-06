#include "Window.h"
#include "Debug.h"
#include "CoreEngine.h"

Window::Window() {
	window = nullptr;
	width = 0;
	height = 0;
}

Window::~Window() {
}

bool Window::OnCreate(std::string name_, int width_, int height_) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::fatalError("SDL failed to initialize", "Window.cpp", __LINE__);
		return false;
	}

	width = width_;
	height = height_;

	renderer = CoreEngine::getInstance()->GetRenderer();

	window = renderer->CreateWindow(name_, width_, height_);

	if (!window) {
		Debug::fatalError("Window failed to create!", "Window.cpp", __LINE__);
		return false;
	}
	
	return true;
}

void Window::OnDestroy() {
	
	SDL_DestroyWindow(window);
	
	window = nullptr;
}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

SDL_Window* Window::getWindow() const {
	return window;
}

