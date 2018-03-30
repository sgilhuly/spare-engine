#pragma once

#include <GL/glew.h>

#include "shader.h"

namespace spare {
class ShaderProgram {
public:
	ShaderProgram();
	bool Init();
	void Cleanup();

	GLuint id = 0;

	GLint attrib_position = -1;
	GLint attrib_uv = -1;
	GLint attrib_normal = -1;

	GLint uniform_m = -1;
	GLint uniform_v = -1;
	GLint uniform_mvp = -1;
	GLint uniform_tex = -1;
	GLint uniform_light_position = -1;

	Shader vertex_shader;
	Shader fragment_shader;
};
}  // namespace spare
