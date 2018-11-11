#include "spare/phiz/bsphere.h"

namespace spare {

Intersection BSphere::IntersectBSphere(const BSphere &other) const {
  float distance = glm::distance(centre, other.centre);
  float radius_sum = radius + other.radius;

  return {distance < radius_sum, distance - radius_sum};
}

}  // namespace spare
