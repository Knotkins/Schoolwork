#include "OpenGLRenderer.h"
#include "Debug.h"

OpenGLRenderer::OpenGLRenderer()
{
}

OpenGLRenderer::~OpenGLRenderer()
{
	SDL_GL_DeleteContext(context);
}

SDL_Window* OpenGLRenderer::CreateWindow(std::string name_, int width_, int height_)
{
	/*if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::fatalError("SDL failed to initialize", "Window.cpp", __LINE__);
		return nullptr;
	}*/

	/*width = width_;
	height = height_;*/

	setPreAttributes();

	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_OPENGL);

	context = SDL_GL_CreateContext(window);

	setPostAttributes();

	GLenum error = glewInit();

	if (error != GLEW_OK) {
		Debug::fatalError("GLEW failed to initialize", "Window.cpp", __LINE__);
		return nullptr;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width_, height_);

	std::cout << "Graphics card: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	return window;
}

void OpenGLRenderer::setPreAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void OpenGLRenderer::setPostAttributes() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
