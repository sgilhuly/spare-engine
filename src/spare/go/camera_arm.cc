#include "spare/go/camera_arm.h"

#include <cmath>

#include "SDL2/SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace spare {

constexpr float mouse_x_speed = 0.01f;
constexpr float mouse_y_speed = 0.01f;

CameraArm::CameraArm(GoTree *tree) : Go(tree) {}

CameraArm::~CameraArm() {}

void CameraArm::Update(float delta) {
  int x = 0;
  int y = 0;
  int state = SDL_GetRelativeMouseState(&x, &y);

  if (state) {
    yaw += x * mouse_x_speed;
    yaw = std::fmod(yaw, M_PI * 2);
    pitch += y * mouse_y_speed;
    pitch = std::fmin(std::fmax(pitch, -M_PI / 3), M_PI / 3);

    rotation = glm::angleAxis(pitch, glm::vec3(1, 0, 0)) *
               glm::angleAxis(yaw, glm::vec3(0, 1, 0));
    dirty = true;
  }
}

}  // namespace spare
