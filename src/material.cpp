#include "material.h"

#include "texture.h"

namespace spare {
Material::Material() {
}

void Material::InitDN(Texture* diffuse, Texture* normal) {
	this->diffuse = diffuse;
	this->normal = normal;
	this->specular = diffuse;
}

void Material::InitDNS(Texture* diffuse, Texture* normal, Texture* specular) {
	this->diffuse = diffuse;
	this->normal = normal;
	this->specular = specular;
}
}