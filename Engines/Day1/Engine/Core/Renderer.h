#ifndef RENDERER_H
#define RENDERER_H
#include <SDL.h>
#include <string>

enum class RenderType : unsigned short {
	TYPE_OPENGL
};

class Renderer {
public:
	Renderer() {};
	~Renderer() {};
	virtual SDL_Window* CreateWindow(std::string name_, int width_, int height_) = 0;
private:
	//virtual void setPreAttributes() = 0;
	//virtual void setPostAttributes() = 0;
};

#endif // !RENDERER_H
