#pragma once

#include <string>
#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"

namespace spare {
class Mesh {
 public:
  Mesh();
  bool Init(const std::string &objpath);

  GLuint vertex_buffer = 0;
  GLuint uv_buffer = 0;
  GLuint normal_buffer = 0;
  GLuint tangent_buffer = 0;
  GLuint bitangent_buffer = 0;
  GLuint element_buffer = 0;
  std::vector<uint16_t> indices;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> tangents;
  std::vector<glm::vec3> bitangents;

 private:
  bool LoadAssimp(const std::string &path);
};
}  // namespace spare
