#include "game_object.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>

using std::cout;
using std::endl;

bool loadAssImp(
		const std::string& path,
		std::vector<uint16_t>& indices,        // NOLINT(runtime/references)
		std::vector<glm::vec3>& vertices,      // NOLINT(runtime/references)
		std::vector<glm::vec2>& uvs,           // NOLINT(runtime/references)
		std::vector<glm::vec3>& normals,       // NOLINT(runtime/references)
		std::vector<glm::vec3>& tangents,      // NOLINT(runtime/references)
		std::vector<glm::vec3>& bitangents) {  // NOLINT(runtime/references)
	Assimp::Importer importer;

	unsigned int flags = aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace;
	const aiScene* scene = importer.ReadFile(path, flags);
	if (!scene) {
		cout << importer.GetErrorString();
		return false;
	}
	// In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)
	const aiMesh* mesh = scene->mMeshes[0];

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		// Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		aiVector3D UVW = mesh->mTextureCoords[0][i];
		uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}

	// Fill vertices tangents
	tangents.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D n = mesh->mTangents[i];
		tangents.push_back(glm::vec3(n.x, n.y, n.z));
	}

	// Fill vertices bitangents
	bitangents.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D n = mesh->mBitangents[i];
		bitangents.push_back(glm::vec3(n.x, n.y, n.z));
	}

	// Fill face indices
	indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}

	// The "scene" pointer will be deleted automatically by "importer"
	return true;
}

namespace spare {
GameObject::GameObject() {
	transform = glm::mat4(1.0f);
}

bool GameObject::Init(const std::string& filepath) {
	if (!loadAssImp(filepath, indices, vertices, uvs, normals, tangents, bitangents)) {
		cout << "Failed to load " << filepath << endl;
		return false;
	}

	// computeTangentBasis(vertices, uvs, normals, tangents, bitangents);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(decltype(vertices)::value_type),
		&vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		uvs.size() * sizeof(decltype(uvs)::value_type),
		&uvs[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &tangent_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangent_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		tangents.size() * sizeof(decltype(tangents)::value_type),
		&tangents[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &bitangent_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangent_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		bitangents.size() * sizeof(decltype(bitangents)::value_type),
		&bitangents[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		normals.size() * sizeof(decltype(normals)::value_type),
		&normals[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &element_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(decltype(indices)::value_type),
		&indices[0],
		GL_STATIC_DRAW);

	cout << "Number of vertices: " << vertices.size() << endl;
	cout << "Number of indices: " << indices.size() << endl;

	return true;
}

void GameObject::OnLoop(float delta) {
	// transform = glm::rotate(transform, delta, glm::vec3(0, 1, 0));
}
}  // namespace spare
