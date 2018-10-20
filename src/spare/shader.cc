#include "spare/shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "GL/glew.h"

using std::cout;
using std::endl;

void printShaderLog(GLuint shader) {
  // Make sure name is shader
  if (glIsShader(shader)) {
    // Shader log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    // Get info string length
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    // Allocate string
    char *infoLog = new char[maxLength];

    // Get info log
    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
      // Print Log
      cout << infoLog << endl;
    } else {
      cout << "Nothing logged" << endl;
    }

    // Deallocate string
    delete[] infoLog;
  } else {
    cout << "Name " << shader << " is not a shader" << endl;
  }
}

namespace spare {
Shader::Shader() {}

bool Shader::InitFromSource(const char *shader_source[],
                            bool is_vertex_shader) {
  id = glCreateShader(is_vertex_shader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
  glShaderSource(id, 1, shader_source, NULL);
  glCompileShader(id);

  GLint success = GL_FALSE;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (success != GL_TRUE) {
    cout << "Unable to compile ";
    cout << (is_vertex_shader ? "vertex" : "fragment");
    cout << " shader " << id << endl;
    cout << "Shader source is:" << endl << shader_source << endl;
    printShaderLog(id);
    return false;
  }

  return true;
}

bool Shader::InitFromFile(const std::string &filepath, bool is_vertex_shader) {
  std::string shader_source;
  std::ifstream shader_stream(filepath, std::ios::in);
  if (shader_stream.is_open()) {
    std::stringstream sstr;
    sstr << shader_stream.rdbuf();
    shader_source = sstr.str();
    shader_stream.close();
  } else {
    cout << "Could not open " << filepath << endl;
    return false;
  }

  const char *source_pointer = shader_source.c_str();
  return InitFromSource(&source_pointer, is_vertex_shader);
}
}  // namespace spare
