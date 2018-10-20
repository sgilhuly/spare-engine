#pragma once

#include <string>

#include "GL/glew.h"

namespace spare {
class Shader {
 public:
  Shader();
  bool InitFromSource(const char *shader_source[], bool is_vertex_shader);
  bool InitFromFile(const std::string &filepath, bool is_vertex_shader);

  GLuint id = 0;
};
}  // namespace spare
