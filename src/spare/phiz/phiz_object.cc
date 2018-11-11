#include "spare/phiz/phiz_object.h"

namespace spare {

void PhizObject::Integrate(float delta, Spatial &spatial) {
  spatial.position += velocity * delta;
}

}  // namespace spare
