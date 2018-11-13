#pragma once

#include "spare/shader_program.h"
#include "spare/texture.h"

namespace spare {
class Material {
 public:
  Material();
  void InitDNR(Texture *diffuse, Texture *normal, Texture *rad,
               ShaderProgram *shader);

  Texture *diffuse;
  Texture *normal;
  Texture *rad;
  ShaderProgram *shader;
};
}  // namespace spare
