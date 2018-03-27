#pragma once

#include <string>

#include <GL/glew.h>

namespace spare {
class Texture {
public:
	Texture();
	bool InitDds(const std::string& imagepath); // Load a DXT1, 3, or 5 compressed texture
	bool InitBmp(const std::string& imagepath); // Load a BMP uncompressed texture
	void Cleanup();

	GLuint id = 0;
};
}