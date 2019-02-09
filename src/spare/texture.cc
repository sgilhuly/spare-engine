#include "spare/texture.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "GL/glew.h"
#include "stb_image.h"

using std::cout;
using std::endl;

#define FOURCC_DXT1 0x31545844  // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844  // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844  // Equivalent to "DXT5" in ASCII

namespace spare {
namespace {

GLuint loadImageStb(const char *imagepath) {
  int width, height, format;
  uint8_t *data = stbi_load(imagepath, &width, &height, &format, 0);
  if (!data) {
    cout << imagepath << " could not be opened" << endl;
    return 0;
  }

  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  int mode = GL_RGB;
  if (format == STBI_rgb_alpha) {
    mode = GL_RGBA;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode,
               GL_UNSIGNED_BYTE, data);

  // Poor filtering, or ...
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // ... nice trilinear filtering ...
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  // ... which requires mipmaps. Generate them automatically.
  glGenerateMipmap(GL_TEXTURE_2D);

  return textureID;
}

}  // namespace

Texture::Texture() {}

bool Texture::Init(const std::string &imagepath) {
  if (!(id = loadImageStb(imagepath.c_str()))) {
    cout << "Failed to load " << imagepath << " as an image" << endl;
    return false;
  }

  return true;
}

void Texture::Cleanup() {
  glDeleteTextures(1, &id);
  id = 0;
}
}  // namespace spare

