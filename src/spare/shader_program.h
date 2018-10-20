#pragma once

#include <string>

#include "GL/glew.h"

#include "spare/shader.h"

namespace spare {
class ShaderProgram {
 public:
  ShaderProgram();
  bool Init(const std::string &name);
  void Cleanup();

  GLuint id = 0;

  GLint attrib_position = -1;
  GLint attrib_uv = -1;
  GLint attrib_normal = -1;
  GLint attrib_tangent = -1;
  GLint attrib_bitangent = -1;

  GLint uniform_m = -1;
  GLint uniform_v = -1;
  GLint uniform_mv = -1;
  GLint uniform_mvp = -1;
  GLint uniform_tex_diffuse = -1;
  GLint uniform_tex_normal = -1;
  GLint uniform_tex_specular = -1;
  GLint uniform_light_position = -1;
  GLint uniform_lighting_options = -1;

  Shader vertex_shader;
  Shader fragment_shader;
};
}  // namespace spare
