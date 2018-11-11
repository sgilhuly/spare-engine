#pragma once

#include "glm/glm.hpp"

#include "spare/phiz/intersection.h"

namespace spare {

struct AABB {
  glm::vec3 min;
  glm::vec3 max;

  Intersection IntersectAABB(const AABB &other) const;
};

}  // namespace spare
