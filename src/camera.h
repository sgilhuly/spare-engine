#pragma once

#include "glm/glm.hpp"

namespace spare {
class Camera {
public:
	Camera();
	void Init(int width, int height);
	void OnLoop(float delta);

	float fov;
	float aspect_ratio;
	float near_clip;
	float far_clip;
	float pitch = 30.0f;
	float rotation = 30.0f;

	glm::mat4 projection;
	glm::mat4 view;
};
}  // namespace spare
