#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "fps.h"

namespace spare {
class Engine {
public:
	Engine();
	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event& event);
	void OnLoop();
	void OnRender();
	void OnCleanup();
private:
	bool running = true;
	FpsCounter fps;
	SDL_Window* window = NULL;
	SDL_GLContext context;

	bool show_quad = true;
	GLuint program_id = 0;
	GLint attrib_position = -1;
	GLuint vbo = 0;
	GLuint ibo = 0;
};
} // namespace spare