#include "spare/resource_loader.h"

#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;

namespace spare {
namespace {

bool icompare_pred(unsigned char a, unsigned char b) {
  return std::tolower(a) == std::tolower(b);
}

bool string_has_extension(const std::string &a, const std::string &b) {
  int length_dif = a.length() - b.length();
  if (length_dif >= 0) {
    return std::equal(b.begin(), b.end(), a.begin() + length_dif,
                      icompare_pred);
  } else {
    return false;
  }
}

}  // namespace

ResourceLoader::ResourceLoader() {}

// Material *ResourceLoader::GetMaterial(const std::string &filename) {
//   return GetMaterial(filename + ".png", filename + "_norm.png",
//                      filename + "_spec.png");
// }

Material *ResourceLoader::GetMaterial(const std::string &diffuse,
                                      const std::string &normal,
                                      const std::string &rad,
                                      const std::string &shader) {
  if (materials.count(diffuse)) {
    return materials[diffuse];
  }

  cout << "Loading new material: " << diffuse << endl;

  Texture *diffuse_tex = GetTexture(diffuse);
  Texture *normal_tex = GetTexture(normal);
  Texture *rad_tex = GetTexture(rad);
  ShaderProgram *shader_program = GetShaderProgram(shader);

  if (!diffuse_tex || !normal_tex || !rad_tex || !shader_program) {
    return NULL;
  }

  Material *material = new Material();
  material->InitDNR(diffuse_tex, normal_tex, rad_tex, shader_program);

  materials[diffuse] = material;
  return material;
}

MeshData *ResourceLoader::GetMesh(const std::string &filename) {
  if (meshes.count(filename)) {
    return meshes[filename];
  }

  cout << "Loading new mesh: " << filename << endl;

  MeshData *mesh = new MeshData();
  if (!mesh->Init(filename)) {
    delete mesh;
    return NULL;
  }

  meshes[filename] = mesh;
  return mesh;
}

ShaderProgram *ResourceLoader::GetShaderProgram(const std::string &filename) {
  if (shaders.count(filename)) {
    return shaders[filename];
  }

  cout << "Loading new shader program: " << filename << endl;

  ShaderProgram *shader = new ShaderProgram();
  if (!shader->Init(filename)) {
    delete shader;
    return NULL;
  }

  shaders[filename] = shader;
  return shader;
}

Texture *ResourceLoader::GetTexture(const std::string &filename) {
  if (textures.count(filename)) {
    return textures[filename];
  }

  cout << "Loading new texture: " << filename << endl;

  Texture *texture = new Texture();

  if (!texture->Init(filename)) {
    delete texture;
    return NULL;
  }

  textures[filename] = texture;
  return texture;
}
}  // namespace spare
