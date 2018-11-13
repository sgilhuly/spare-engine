#pragma once

#include "glm/glm.hpp"

#include "spare/phiz/intersection.h"

namespace spare {

struct BSphere {
  glm::vec3 centre;
  float radius;

  Intersection IntersectBSphere(const BSphere &other) const;
};

}  // namespace spare
