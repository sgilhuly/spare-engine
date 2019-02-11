#include "spare/go/rotator.h"

#include <iostream>

namespace spare {

Rotator::Rotator(GoTree *tree, float angle, const glm::vec3 &axis)
    : Go(tree), angle_(angle), axis_(axis) {}

Rotator::~Rotator() {}

void Rotator::Update(float delta) {
  Rotate(angle_ * delta, axis_);
}

}  // namespace spare
