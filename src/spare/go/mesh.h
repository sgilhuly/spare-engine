#pragma once

#include "glm/glm.hpp"

#include "spare/go/go.h"
#include "spare/material.h"
#include "spare/mesh_data.h"

namespace spare {

class Mesh : public Go {
 public:
  Mesh(GoTree *tree, MeshData *mesh, Material *material);
  ~Mesh() override;

  void Draw(const glm::mat4 &projection, const glm::mat4 &view) override;

 protected:
  MeshData *mesh;
  Material *material;
};

}  // namespace spare
