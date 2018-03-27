#include "shader_program.h"

#include <iostream>

#include <GL/glew.h>

#include "shader.h"

using std::cout;
using std::endl;

void printProgramLog( GLuint program )
{
	//Make sure name is shader
	if( glIsProgram( program ) )
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		
		//Get info string length
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
		
		//Allocate string
		char* infoLog = new char[ maxLength ];
		
		//Get info log
		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			cout << infoLog << endl;
		}
		else
		{
			cout << "Nothing logged" << endl;
		}
		
		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		cout << "Name " << program << " is not a program" << endl;
	}
}

namespace spare {
ShaderProgram::ShaderProgram() {
}

bool ShaderProgram::Init() {
	// For now, hardcode some simple shaders
	const GLchar* vertex_shader_source[] = {
		"#version 330 core\n"
		"in vec3 vertex_position;\n"
		"in vec2 vertex_uv;\n"
		"out vec2 uv;\n"
		"uniform mat4 mvp;\n"
		"void main() {\n"
		"	gl_Position = mvp * vec4(vertex_position, 1);\n"
		"	uv = vertex_uv;\n"
		"}\n",
	};

	const GLchar* fragment_shader_source[] = {
		"#version 330 core\n"
		"in vec2 uv;\n"
		"out vec3 colour;\n"
		"uniform sampler2D tex;\n"
		"void main() {\n"
		"	colour = texture(tex, uv).rgb;"
		"}\n",
	};

	id = glCreateProgram();

	if (!vertex_shader.InitFromSource(vertex_shader_source, true)) {
		cout << "Program failed due to vertex shader errors" << endl;
		return false;
	}
	glAttachShader(id, vertex_shader.id);

	if (!fragment_shader.InitFromSource(fragment_shader_source, false)) {
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
	uniform_mvp = glGetUniformLocation(id, "mvp");
	uniform_tex = glGetUniformLocation(id, "tex");

	return true;
}

void ShaderProgram::Cleanup() {
	glDeleteProgram(id);
	id = 0;
}
}