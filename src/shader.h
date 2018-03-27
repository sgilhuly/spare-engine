#pragma once

#include <GL/glew.h>

namespace spare {
class Shader {
public:
	Shader();
	bool InitFromSource(const GLchar* shader_source[], bool is_vertex_shader);

	GLuint id = 0;
};
}