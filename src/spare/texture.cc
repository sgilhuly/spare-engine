#include "spare/texture.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using std::cout;
using std::endl;

#define FOURCC_DXT1 0x31545844  // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844  // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844  // Equivalent to "DXT5" in ASCII

namespace spare {
namespace {

GLuint loadImageSdl(const char *imagepath) {
  SDL_Surface *surface = IMG_Load(imagepath);
  if (surface == NULL) {
    cout << imagepath << " could not be opened" << endl;
    return 0;
  }

  // Flip the image by swapping the rows, outside to in.
  uint8_t *temp_row = new uint8_t[surface->pitch];
  int rows_to_swap = static_cast<int>(surface->h * 0.5f);
  for (int i = 0; i < rows_to_swap; i++) {
    memcpy(temp_row,
           static_cast<uint8_t *>(surface->pixels) + (surface->pitch * i),
           surface->pitch);
    memcpy(static_cast<uint8_t *>(surface->pixels) + (surface->pitch * i),
           static_cast<uint8_t *>(surface->pixels) +
               (surface->pitch * (surface->h - i - 1)),
           surface->pitch);
    memcpy(static_cast<uint8_t *>(surface->pixels) +
               (surface->pitch * (surface->h - i - 1)),
           temp_row, surface->pitch);
  }
  delete[] temp_row;

  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  int mode = GL_RGB;
  if (surface->format->BytesPerPixel == 4) {
    mode = GL_RGBA;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode,
               GL_UNSIGNED_BYTE, surface->pixels);
  SDL_FreeSurface(surface);
  surface = NULL;

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
  if (!(id = loadImageSdl(imagepath.c_str()))) {
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
