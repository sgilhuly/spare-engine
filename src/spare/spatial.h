#pragma once

#include <map>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace spare {

struct Spatial {
  glm::vec3 position;
  glm::quat rotation;

  glm::mat4 GetTransform() const;
};

}  // namespace spare
