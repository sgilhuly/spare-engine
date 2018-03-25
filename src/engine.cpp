#include "engine.h"

#include <cstdio>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "fps.h"

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

void printShaderLog( GLuint shader )
{
	//Make sure name is shader
	if( glIsShader( shader ) )
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		
		//Get info string length
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
		
		//Allocate string
		char* infoLog = new char[ maxLength ];
		
		//Get info log
		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
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
		cout << "Name " << shader << " is not a shader" << endl;
	}
}

namespace spare {
Engine::Engine() {
	/*running = true;
	window = NULL;

	show_quad = true;
	program_id = 0;
	attrib_position = -1;
	vbo = 0;
	ibo = 0;*/
}

int Engine::OnExecute() {
	if (!OnInit()) {
		return -1;
	}

	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			OnEvent(event);
		}
		OnLoop();
		OnRender();

		if(fps.update()) {
			char title[64];
			sprintf(title, "SDL Tutorial - %0.2f FPS", fps.getFps());

			SDL_SetWindowTitle(window, title);
		}
	}

	OnCleanup();

	return 0;
}

bool Engine::OnInit() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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

	program_id = glCreateProgram();

	// Create and attach vertex shader
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertex_shader_source[] = {
		"#version 330 core\n"
		"layout(location = 0) in vec3 position_modelspace;\n"
		"void main() {\n"
		"	gl_Position.xyz = position_modelspace;\n"
		"	gl_Position.w = 1.0;\n"
		"}\n",
		//"#version 330\nin vec2 VertexPos2D; void main() { gl_Position = vec4( VertexPos2D.x, VertexPos2D.y, 0, 1 ); }"
	};
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	GLint success = GL_FALSE;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		cout << "Unable to compile vertex shader " << vertex_shader << endl;
		printShaderLog(vertex_shader);
		return false;
	}
	glAttachShader(program_id, vertex_shader);

	// Create and attach fragment shader
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragment_shader_source[] = {
		"#version 330 core\n"
		"out vec3 colour;\n"
		"void main() {\n"
		"	colour = vec3(1.0, 0.5, 0.5);"
		"}\n",
		//"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 0.5, 0.5, 1.0 ); }"
	};
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		cout << "Unable to compile fragment shader " << fragment_shader << endl;
		printShaderLog(fragment_shader);
		return false;
	}
	glAttachShader(program_id, fragment_shader);

	// Link the program
	glLinkProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		cout << "Error linking program " << program_id;
		printProgramLog(program_id);
		return false;
	}

	attrib_position = glGetAttribLocation(program_id, "position_modelspace");
	if (attrib_position == -1) {
		cout << "position_modelspace is not a valid glsl program variable" << endl;
		return false;
	}

	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	glClearColor(0.1f, 0.2f, 0.3f, 1);
	GLfloat vertex_data[] = {
		-0.6f, -0.6f, 0,
		0.4f, -0.4f, 0,
		-0.4f, 0.4f, 0
	};
	//GLuint index_data[] = {0, 1, 2, 3};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	//glGenBuffers(1, &ibo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

	return true;
}

void Engine::OnEvent(SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;

		case SDL_KEYDOWN:
			show_quad = !show_quad;
			break;
	}
}

void Engine::OnLoop() {
	//
}

void Engine::OnRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (show_quad) {
		glUseProgram(program_id);
		glEnableVertexAttribArray(0);

		//glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//glVertexAttribPointer(attrib_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glUseProgram(0);
	}

	SDL_GL_SwapWindow(window);
}

void Engine::OnCleanup() {
	glDeleteProgram(program_id);
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}
} // namespace spare