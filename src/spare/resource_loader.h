#pragma once

#include <map>
#include <string>

#include "spare/material.h"
#include "spare/mesh.h"
#include "spare/shader_program.h"
#include "spare/texture.h"

namespace spare {
class ResourceLoader {
 public:
  ResourceLoader();
  Material *GetMaterial(const std::string &filename);
  Material *GetMaterial(const std::string &diffuse, const std::string &normal,
                        const std::string &rad);
  Mesh *GetMesh(const std::string &filename);
  ShaderProgram *GetShaderProgram(const std::string &filename);
  Texture *GetTexture(const std::string &filename);

 private:
  std::map<std::string, Material *> materials;
  std::map<std::string, Mesh *> meshes;
  std::map<std::string, ShaderProgram *> shaders;
  std::map<std::string, Texture *> textures;
};
}  // namespace spare
