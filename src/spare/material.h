#pragma once

#include "texture.h"

namespace spare {
class Material {
public:
	Material();
	void InitDN(Texture* diffuse, Texture* normal);
	void InitDNS(Texture* diffuse, Texture* normal, Texture* specular);

	Texture* diffuse = NULL;
	Texture* normal = NULL;
	Texture* specular = NULL;
};
}  // namespace spare
