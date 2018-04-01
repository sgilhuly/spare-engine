#include "shader_program.h"

#include <iostream>

#include <GL/glew.h>

#include "shader.h"

using std::cout;
using std::endl;

void printProgramLog(GLuint program) {
	// Make sure name is shader
	if (glIsProgram(program)) {
		// Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		// Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// Allocate string
		char* infoLog = new char[maxLength];

		// Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0) {
			// Print Log
			cout << infoLog << endl;
		} else {
			cout << "Nothing logged" << endl;
		}

		// Deallocate string
		delete[] infoLog;
	} else {
		cout << "Name " << program << " is not a program" << endl;
	}
}

namespace spare {
ShaderProgram::ShaderProgram() {
}

bool ShaderProgram::Init() {
	id = glCreateProgram();

	if (!vertex_shader.InitFromFile("stuff/basic_lighting.vertex", true)) {
		cout << "Program failed due to vertex shader errors" << endl;
		return false;
	}
	glAttachShader(id, vertex_shader.id);

	if (!fragment_shader.InitFromFile("stuff/basic_lighting.fragment", false)) {
		cout << "Program failed due to fragment shader errors" << endl;
		return false;
	}
	glAttachShader(id, fragment_shader.id);

	GLint success = GL_FALSE;
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		cout << "Error linking program " << id << endl;
		printProgramLog(id);
		return false;
	}

	// For now, use hardcoded program variables
	attrib_position = glGetAttribLocation(id, "vertex_position");
	attrib_uv = glGetAttribLocation(id, "vertex_uv");
	attrib_normal = glGetAttribLocation(id, "vertex_normal");
	attrib_tangent = glGetAttribLocation(id, "vertex_tangent");
	attrib_bitangent = glGetAttribLocation(id, "vertex_bitangent");

	uniform_m = glGetUniformLocation(id, "m");
	uniform_v = glGetUniformLocation(id, "v");
	uniform_mv = glGetUniformLocation(id, "mv");
	uniform_mvp = glGetUniformLocation(id, "mvp");
	uniform_tex_diffuse = glGetUniformLocation(id, "tex_diffuse");
	uniform_tex_normal = glGetUniformLocation(id, "tex_normal");
	uniform_tex_specular = glGetUniformLocation(id, "tex_specular");
	uniform_light_position = glGetUniformLocation(id, "light_position");
	uniform_lighting_options = glGetUniformLocation(id, "lighting_options");

	return true;
}

void ShaderProgram::Cleanup() {
	glDeleteProgram(id);
	id = 0;
}
}  // namespace spare
