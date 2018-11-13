#pragma once

#include "spare/go/go.h"

namespace spare {

class Camera : public Go {
 public:
  Camera(GoTree *tree, int width, int height, float fov, float near_clip,
         float far_clip);
  ~Camera() override;

  const glm::mat4 &GetProjection() const { return projection; }
  const glm::mat4 &GetView() const { return view; }

  void Update(float delta) override;

 protected:
  glm::mat4 projection;
  glm::mat4 view;
};

}  // namespace spare
