#pragma once

#include <map>

#include "glm/glm.hpp"

namespace spare {

struct Spatial {
  glm::mat4 transform;
  float rotate_speed;

  void Update(float delta);
};

}  // namespace spare
