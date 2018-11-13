#include "spare/material.h"

#include "spare/texture.h"

namespace spare {
Material::Material() {}

void Material::InitDNR(Texture *diffuse, Texture *normal, Texture *rad,
                       ShaderProgram *shader) {
  this->diffuse = diffuse;
  this->normal = normal;
  this->rad = rad;
  this->shader = shader;
}
}  // namespace spare
