#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace spare {
class GameObject {
public:
	GameObject();
	bool Init(const std::string& objpath);
	void OnLoop(float delta);

	glm::mat4 transform;

	GLuint vertex_buffer = 0;
	GLuint uv_buffer = 0;
	GLuint normal_buffer = 0;
	GLuint tangent_buffer = 0;
	GLuint bitangent_buffer = 0;
	GLuint element_buffer = 0;
	std::vector<uint16_t> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
};
}  // namespace spare
