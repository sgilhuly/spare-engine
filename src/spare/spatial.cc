#include "spare/spatial.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace spare {

void Spatial::Update(float delta) {
  transform = glm::rotate(transform, rotate_speed * delta, glm::vec3(0, 1, 0));
}

}  // namespace spare
