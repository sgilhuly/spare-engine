#pragma once

#include "spare/texture.h"

namespace spare {
class Material {
 public:
  Material();
  void InitDNR(Texture *diffuse, Texture *normal, Texture *rad);

  Texture *diffuse = NULL;
  Texture *normal = NULL;
  Texture *rad = NULL;
};
}  // namespace spare
