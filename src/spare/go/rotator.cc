#include "spare/go/rotator.h"

#include <iostream>

#include "glm/gtx/io.hpp"

namespace spare {

Rotator::Rotator(GoTree *tree, float angle, const glm::vec3 &axis)
    : Go(tree), angle_(angle), axis_(axis) {}

Rotator::~Rotator() {}

void Rotator::Update(float delta) {
  Rotate(glm::angleAxis(angle_ * delta, axis_));
//  std::cout << "Rotation was " << rotation << std::endl;
//  std::cout << "Delta is " << delta << std::endl;
//  std::cout << "AngV is " << angular_velocity_ << std::endl;
//  std::cout << "Rotation is " << rotation << std::endl;
}

}  // namespace spare
