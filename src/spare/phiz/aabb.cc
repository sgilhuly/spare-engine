#include "spare/phiz/aabb.h"

#include <algorithm>

namespace spare {

Intersection AABB::IntersectAABB(const AABB &other) const {
  glm::vec3 min_vs_max = min - other.max;
  glm::vec3 max_vs_min = other.min - max;
  glm::vec3 distance = glm::max(min_vs_max, max_vs_min);
  float component_max = std::max(distance.x, std::max(distance.y, distance.z));

  return {component_max < 0, component_max};
}

}  // namespace spare
