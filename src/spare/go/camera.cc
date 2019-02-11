#include "spare/go/camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "spare/go/go_tree.h"

namespace spare {

Camera::Camera(GoTree *tree, int width, int height, float fov, float near_clip,
               float far_clip)
    : Go(tree) {
  tree->SetPrimaryCamera(this);
  float aspect_ratio = (width * 1.0f) / height;
  projection =
      glm::perspective(glm::radians(fov), aspect_ratio, near_clip, far_clip);
};

Camera::~Camera(){};

void Camera::Update(float delta) {
  view =
      glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0)) *
      global_transform;
}

}  // namespace spare
