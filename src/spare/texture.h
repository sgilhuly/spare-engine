#pragma once

#include <string>

#include <GL/glew.h>

namespace spare {
class Texture {
public:
	Texture();
	// Load a DXT1, 3, or 5 compressed texture
	bool InitDds(const std::string& imagepath);
	// Load a regular image texture through SDL
	bool Init(const std::string& imagepath);
	void Cleanup();

	GLuint id = 0;
};
}  // namespace spare
