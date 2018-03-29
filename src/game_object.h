#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace spare {
class GameObject {
public:
	GameObject();
	bool InitObj(const std::string& objpath);
	void OnLoop(float delta);
	//void OnRender(float delta);

	glm::mat4 transform;

	GLuint vertex_buffer = 0;
	GLuint uv_buffer = 0;
	GLuint normal_buffer = 0;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
};
} // namespace spare
