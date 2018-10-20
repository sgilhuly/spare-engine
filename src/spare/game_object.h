#pragma once

// class GameObject;  // need to forward declare for circular dependancy

#include <map>

#include "glm/glm.hpp"

#include "spare/material.h"
#include "spare/mesh.h"
#include "spare/shader_program.h"

namespace spare {
class GameObject {
 public:
  GameObject();
  void OnLoop(float delta);

  Material *material;
  Mesh *mesh;
  ShaderProgram *shader;

  glm::mat4 transform;

 private:
  // std::map<std::string, Component*> components;
};
}  // namespace spare
