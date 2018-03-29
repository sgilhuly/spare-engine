#include "camera.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>

const float mouse_x_speed = 0.5f;
const float mouse_y_speed = 0.5f;
const float camera_distance = 5.0f;
const float pi = 3.1415927f;

namespace spare {
Camera::Camera() {
}

void Camera::Init(int width, int height) {
	fov = 45.0f;
	aspect_ratio = (width * 1.0f) / height;
	near_clip = 0.1f;
	far_clip = 100.0f;

	projection = glm::perspective(glm::radians(fov), aspect_ratio, near_clip, far_clip);
	OnLoop(0); // Call the loop function to set the view matrix
	//view = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
}

void Camera::OnLoop(float delta) {
	int x = 0;
	int y = 0;
	SDL_GetRelativeMouseState(&x, &y);

	rotation += x * mouse_x_speed * delta;
	rotation = std::fmod(rotation, 2 * pi);
	pitch += y * mouse_y_speed * delta;
	pitch = std::fmin(std::fmax(pitch, -pi / 3), pi / 3);

	float cam_x = cos(rotation) * cos(pitch) * camera_distance;
	float cam_y = sin(pitch) * camera_distance;
	float cam_z = sin(rotation) * cos(pitch) * camera_distance;

	view = glm::lookAt(glm::vec3(cam_x, cam_y, cam_z), glm::vec3(0,0,0), glm::vec3(0,1,0));
}
} // namespace spare
