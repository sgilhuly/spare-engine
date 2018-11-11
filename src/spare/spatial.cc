#include "spare/spatial.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace spare {

glm::mat4 Spatial::GetTransform() const {
  return glm::translate(glm::mat4(1.f), position);
}

}  // namespace spare
