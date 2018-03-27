#include "engine.h"

#include <cstdio>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "camera.h"
#include "fps.h"
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

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};

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

	while (running) {
		this_time = SDL_GetTicks();
		delta = (this_time - last_time) / 1000.0f;
		last_time = this_time;

		while (SDL_PollEvent(&event)) {
			OnEvent(event);
		}
		OnLoop(delta);
		OnRender(delta);

		if(fps.update()) {
			char title[64];
			sprintf(title, "Spare Engine - %0.2f FPS", fps.getFps());

			SDL_SetWindowTitle(window, title);
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
	glDepthFunc(GL_LESS);
	glClearColor(0.1f, 0.2f, 0.3f, 1);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colour_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, colour_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	//glGenBuffers(1, &ibo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

	camera.Init(width, height);
	if (!texture_bmp.InitBmp("stuff/uvtemplate.bmp")) {
		return false;
	}
	if (!texture_dds.InitDds("stuff/uvtemplate.DDS")) {
		return false;
	}

	return true;
}

void Engine::OnEvent(SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;

		case SDL_KEYDOWN:
			//show_quad = !show_quad;
			break;
	}
}

void Engine::OnLoop(float delta) {
	camera.OnLoop(delta);
}

void Engine::OnRender(float delta) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (show_quad) {
		glUseProgram(program.id);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 mvp = camera.projection * camera.view * model;
		glUniformMatrix4fv(program.uniform_mvp, 1, GL_FALSE, &mvp[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_bmp.id);
		glUniform1i(program.uniform_tex, 0);

		glEnableVertexAttribArray(program.attrib_position);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glVertexAttribPointer(program.attrib_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(program.attrib_uv);
		glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
		glVertexAttribPointer(program.attrib_uv, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//glEnableVertexAttribArray(program.attrib_uv);
		//glBindBuffer(GL_ARRAY_BUFFER, colour_buffer);
		//glVertexAttribPointer(program.attrib_uv, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glDisableVertexAttribArray(program.attrib_position);
		glDisableVertexAttribArray(program.attrib_uv);
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
} // namespace spare