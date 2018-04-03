#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "camera.h"
#include "game_object.h"
#include "shader_program.h"
#include "texture.h"

namespace spare {
class Engine {
public:
	Engine(int width, int height);
	int OnExecute();
	bool OnInit();
	void OnEvent(const SDL_Event& event);
	void OnLoop(float delta);
	void OnRender(float delta);
	void OnCleanup();

private:
	bool running = true;
	Camera camera;
	SDL_Window* window = NULL;
	SDL_GLContext context;
	ShaderProgram program;
	Texture texture_diffuse;
	Texture texture_normal;
	Texture texture_specular;
	Mesh mesh_cylinder;
	Material mat_hp_rock_2;
	std::vector<GameObject> objects;
	glm::vec3 options;

	int width;
	int height;
};
}  // namespace spare
