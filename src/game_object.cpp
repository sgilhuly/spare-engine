#include "game_object.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>

#include "material.h"
#include "mesh.h"
#include "shader_program.h"

namespace spare {
GameObject::GameObject() {
	transform = glm::mat4(1.0f);
}

void GameObject::OnLoop(float delta) {
	// transform = glm::rotate(transform, delta, glm::vec3(0, 1, 0));
}
}  // namespace spare
