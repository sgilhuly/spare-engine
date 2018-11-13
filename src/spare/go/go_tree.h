#pragma once

#include "spare/go/camera.h"
#include "spare/go/go.h"

namespace spare {

class GoTree {
 public:
  GoTree();
  ~GoTree();

  void SetPrimaryCamera(Camera *camera) { primary_camera = camera; }

  void UpdateTree(float delta);
  void DrawTree();

 protected:
  Go *root;
  Camera *primary_camera = nullptr;
};

}  // namespace spare
