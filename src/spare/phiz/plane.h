#pragma once

#include "glm/glm.hpp"

#include "spare/phiz/bsphere.h"
#include "spare/phiz/intersection.h"

namespace spare {

struct Plane {
  glm::vec3 normal;
  float distance;

  Plane Normalized() const;

  Intersection IntersectBSphere(const BSphere &other) const;
};

}  // namespace spare
