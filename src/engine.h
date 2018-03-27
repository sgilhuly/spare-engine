#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "camera.h"
#include "fps.h"
#include "shader_program.h"
#include "texture.h"

namespace spare {
class Engine {
public:
	Engine(int width, int height);
	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event& event);
	void OnLoop(float delta);
	void OnRender(float delta);
	void OnCleanup();
private:
	bool running = true;
	Camera camera;
	FpsCounter fps;
	SDL_Window* window = NULL;
	SDL_GLContext context;
	ShaderProgram program;
	Texture texture_bmp;
	Texture texture_dds;

	int width;
	int height;
	bool show_quad = true;

	GLuint vertex_buffer = 0;
	GLuint colour_buffer = 0;
	GLuint uv_buffer = 0;
	GLuint ibo = 0;
};
} // namespace spare