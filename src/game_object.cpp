#include "game_object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "material.h"
#include "mesh.h"
#include "shader_program.h"

namespace spare {
GameObject::GameObject() {
	transform = glm::mat4(1.0f);
}

void GameObject::OnLoop(float delta) {
	transform = glm::rotate(transform, delta, glm::vec3(0, 1, 0));
}
}  // namespace spare
