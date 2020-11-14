#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include "Renderer.h"
#include <glew.h>
#include <SDL_opengl.h>
#include <iostream>

class OpenGLRenderer : public Renderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();
	virtual SDL_Window* CreateWindow(std::string name_, int width_, int height_);
private:
	virtual void setPreAttributes();
	virtual void setPostAttributes();

	SDL_GLContext context;
	SDL_Window* window;
};

#endif // !OPENGLRENDERER_H
