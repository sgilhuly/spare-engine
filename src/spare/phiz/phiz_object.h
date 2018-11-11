#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "spare/spatial.h"

namespace spare {

struct PhizObject {
  glm::vec3 velocity;
  glm::quat angular_velocity;

  void Integrate(float delta, Spatial &spatial);
};

}  // namespace spare
