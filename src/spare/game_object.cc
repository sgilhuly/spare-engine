#include "spare/game_object.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "spare/material.h"
#include "spare/mesh.h"
#include "spare/shader_program.h"

namespace spare {
GameObject::GameObject() { transform = glm::mat4(1.0f); }

void GameObject::OnLoop(float delta) {
  transform = glm::rotate(transform, delta, glm::vec3(0, 1, 0));
}
}  // namespace spare
