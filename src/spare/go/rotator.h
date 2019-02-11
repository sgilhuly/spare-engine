#pragma once

#include "spare/go/go.h"

namespace spare {

class Rotator : public Go {
 public:
  Rotator(GoTree *tree, float angle, const glm::vec3 &axis);
  ~Rotator() override;

  void Update(float delta) override;

 protected:
  float angle_;
  glm::vec3 axis_;
};

}  // namespace spare
