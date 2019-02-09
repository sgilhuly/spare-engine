#pragma once

#include <string>

#include "GL/glew.h"

namespace spare {
class Texture {
 public:
  Texture();
  // Load a regular image texture through stb
  bool Init(const std::string &imagepath);
  void Cleanup();

  GLuint id = 0;
};
}  // namespace spare
