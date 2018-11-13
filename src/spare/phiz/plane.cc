#include "spare/phiz/plane.h"

#include <cmath>

namespace spare {

Plane Plane::Normalized() const {
  float normal_length = glm::length(normal);
  return {normal / normal_length, distance / normal_length};
}

Intersection Plane::IntersectBSphere(const BSphere &other) const {
  float distance_from_centre =
      std::fabs(glm::dot(normal, other.centre) + distance);
  float distance_from_sphere = distance_from_centre - other.radius;

  return {distance_from_sphere < 0, distance_from_sphere};
}

}  // namespace spare
