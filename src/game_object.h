#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "material.h"
#include "mesh.h"
#include "shader_program.h"

namespace spare {
class GameObject {
public:
	GameObject();
	void OnLoop(float delta);

	Material* material;
	Mesh* mesh;
	ShaderProgram* shader;

	glm::mat4 transform;
};
}  // namespace spare
