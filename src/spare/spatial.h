#pragma once

#include <map>

#include "glm/glm.hpp"

namespace spare {

struct Spatial {
  glm::mat4 transform;

  void Update(float delta);
};

}  // namespace spare
