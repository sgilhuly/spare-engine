#include "engine.h"

#include <cstdio>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "camera.h"
#include "game_object.h"
#include "shader_program.h"
#include "texture.h"

/*extern "C" {
  static int l_cppfunction(lua_State *L) {
    double arg = luaL_checknumber(L,1);
    lua_pushnumber(L, arg * 0.5);
    return 1;
  }
}

using namespace std;*/

using std::cout;
using std::endl;

namespace spare {
Engine::Engine(int width, int height) : width(width), height(height) {
}

int Engine::OnExecute() {
	if (!OnInit()) {
		return -1;
	}

	SDL_Event event;
	int this_time = 0;
	int last_time = SDL_GetTicks();
	float delta = 0;

	int ticks = 0;
	float total_time = 0;

	while (running) {
		this_time = SDL_GetTicks();
		delta = (this_time - last_time) / 1000.0f;
		last_time = this_time;

		while (SDL_PollEvent(&event)) {
			OnEvent(event);
		}
		OnLoop(delta);
		OnRender(delta);

		ticks++;
		total_time += delta;
		if (total_time >= 0.25f) {
			char title[64];
			snprintf(title, sizeof(title), "Spare Engine - %0.2f FPS", ticks / total_time);
			SDL_SetWindowTitle(window, title);

			ticks = 0;
			total_time = 0;
		}
	}

	OnCleanup();

	return 0;
}

bool Engine::OnInit() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("Spare Engine",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "Could not create window: " << SDL_GetError() << endl;
		return false;
	}

	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		cout << "Could not create OpenGL context: " << SDL_GetError() << endl;
		return false;
	}

	glewExperimental = GL_TRUE;
	GLenum glew_error;
	if ((glew_error = glewInit()) != GLEW_OK) {
		cout << "Error initializing GLEW: "
			<< glewGetErrorString(glew_error) << endl;
	}

	if (SDL_GL_SetSwapInterval(1) < 0) {
		cout << "Warning: Unable to set VSync: " << SDL_GetError() << endl;
	}

	if (!program.Init()) {
		return false;
	}

	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.1f, 0.2f, 0.3f, 1);

	camera.Init(width, height);
	if (!texture_bmp.InitBmp("stuff/uvtemplate.bmp")) {
		return false;
	}
	if (!texture_dds.InitDds("stuff/uvtemplate.DDS")) {
		return false;
	}
	if (!monkey.Init("stuff/monkey2.obj")) {
		return false;
	}

	return true;
}

void Engine::OnEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = false;
					break;
			}
			break;
	}
}

void Engine::OnLoop(float delta) {
	camera.OnLoop(delta);
	monkey.OnLoop(delta);
}

void Engine::OnRender(float delta) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (show_quad) {
		glUseProgram(program.id);

		glm::mat4 mvp = camera.projection * camera.view * monkey.transform;
		glm::vec3 light_position(5, -5, 2);
		glUniformMatrix4fv(program.uniform_m, 1, GL_FALSE, &monkey.transform[0][0]);
		glUniformMatrix4fv(program.uniform_v, 1, GL_FALSE, &camera.view[0][0]);
		glUniformMatrix4fv(program.uniform_mvp, 1, GL_FALSE, &mvp[0][0]);
		glUniform3f(program.uniform_light_position, light_position.x, light_position.y, light_position.z);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_bmp.id);
		glUniform1i(program.uniform_tex, 0);

		glEnableVertexAttribArray(program.attrib_position);
		glBindBuffer(GL_ARRAY_BUFFER, monkey.vertex_buffer);
		glVertexAttribPointer(program.attrib_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(program.attrib_uv);
		glBindBuffer(GL_ARRAY_BUFFER, monkey.uv_buffer);
		glVertexAttribPointer(program.attrib_uv, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(program.attrib_normal);
		glBindBuffer(GL_ARRAY_BUFFER, monkey.normal_buffer);
		glVertexAttribPointer(program.attrib_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, monkey.element_buffer);

		glDrawElements(GL_TRIANGLES, monkey.indices.size(), GL_UNSIGNED_SHORT, 0);

		glDisableVertexAttribArray(program.attrib_position);
		glDisableVertexAttribArray(program.attrib_uv);
		glDisableVertexAttribArray(program.attrib_normal);
		glUseProgram(0);
	}

	SDL_GL_SwapWindow(window);
}

void Engine::OnCleanup() {
	program.Cleanup();
	texture_bmp.Cleanup();
	texture_dds.Cleanup();
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}
}  // namespace spare
