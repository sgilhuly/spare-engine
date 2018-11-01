#pragma once

#include "glm/glm.hpp"

#include "spare/material.h"
#include "spare/mesh.h"
#include "spare/shader_program.h"
#include "spare/spatial.h"

namespace spare {

struct Drawable {
  Material *material;
  Mesh *mesh;
  ShaderProgram *shader;
};

class Camera {
 public:
  Camera();
  void Init(int width, int height);
  void OnLoop(float delta);
  void Draw(const Drawable &drawable, const Spatial &spatial,
            const glm::vec4 &options);

  float fov;
  float aspect_ratio;
  float near_clip;
  float far_clip;
  float pitch = glm::radians(30.0f);
  float rotation = glm::radians(0.0f);

  glm::mat4 projection;
  glm::mat4 view;
  glm::vec3 light_position;
};

}  // namespace spare
