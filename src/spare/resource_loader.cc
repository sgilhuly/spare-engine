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

Material *ResourceLoader::GetMaterial(const std::string &filename) {
  if (materials.count(filename)) {
    return materials[filename];
  }

  cout << "Loading new material: " << filename << endl;

  Texture *diffuse = GetTexture(filename + ".png");
  Texture *normal = GetTexture(filename + "_norm.png");
  Texture *specular = GetTexture(filename + "_spec.png");

  if (diffuse == NULL || normal == NULL) {
    return NULL;
  }

  if (specular == NULL) {
    specular = diffuse;
  }

  Material *material = new Material();
  material->InitDNS(diffuse, normal, specular);

  materials[filename] = material;
  return material;
}

Mesh *ResourceLoader::GetMesh(const std::string &filename) {
  if (meshes.count(filename)) {
    return meshes[filename];
  }

  cout << "Loading new mesh: " << filename << endl;

  Mesh *mesh = new Mesh();
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
  bool success;
  if (string_has_extension(filename, ".dds")) {
    success = texture->InitDds(filename);
  } else {
    success = texture->Init(filename);
  }

  if (!success) {
    delete texture;
    return NULL;
  }

  textures[filename] = texture;
  return texture;
}
}  // namespace spare
