#pragma once

#include "spare/go/go.h"

namespace spare {

class CameraArm : public Go {
 public:
  CameraArm(GoTree *tree);
  ~CameraArm() override;

  void Update(float delta) override;

 protected:
  float pitch = 0;
  float yaw = 0;
};

}  // namespace spare
