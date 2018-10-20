#include "spare/camera.h"

#include <cmath>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "spare/game_object.h"

const float mouse_x_speed = 0.5f;
const float mouse_y_speed = 0.5f;
const float camera_distance = 5.0f;
const float pi = 3.1415927f;

namespace spare {
Camera::Camera() {}

void Camera::Init(int width, int height) {
  fov = 45.0f;
  aspect_ratio = (width * 1.0f) / height;
  near_clip = 0.1f;
  far_clip = 100.0f;

  projection =
      glm::perspective(glm::radians(fov), aspect_ratio, near_clip, far_clip);
}

void Camera::OnLoop(float delta) {
  int x = 0;
  int y = 0;
  SDL_GetRelativeMouseState(&x, &y);

  rotation += x * mouse_x_speed * delta;
  rotation = std::fmod(rotation, 2 * pi);
  pitch += y * mouse_y_speed * delta;
  pitch = std::fmin(std::fmax(pitch, -pi / 3), pi / 3);

  float cam_x = 2 * cos(rotation) * cos(pitch) * camera_distance;
  float cam_y = 2 * sin(pitch) * camera_distance;
  float cam_z = 2 * sin(rotation) * cos(pitch) * camera_distance;

  view = glm::lookAt(glm::vec3(cam_x, cam_y, cam_z), glm::vec3(0, 0, 0),
                     glm::vec3(0, 1, 0));

  // Position a light source 2 units above the camera
  light_position = glm::vec3(glm::inverse(view) * glm::vec4(0, 2, 0, 1));
}

void Camera::DrawObject(const GameObject &obj, const glm::vec3 &options) {
  glUseProgram(obj.shader->id);

  glm::mat4 mvp = projection * view * obj.transform;
  glm::mat3 mv = glm::mat3(view * obj.transform);
  glUniformMatrix4fv(obj.shader->uniform_m, 1, GL_FALSE, &obj.transform[0][0]);
  glUniformMatrix4fv(obj.shader->uniform_v, 1, GL_FALSE, &view[0][0]);
  glUniformMatrix3fv(obj.shader->uniform_mv, 1, GL_FALSE, &mv[0][0]);
  glUniformMatrix4fv(obj.shader->uniform_mvp, 1, GL_FALSE, &mvp[0][0]);
  glUniform3f(obj.shader->uniform_light_position, light_position.x,
              light_position.y, light_position.z);
  glUniform3f(obj.shader->uniform_lighting_options, options.x, options.y,
              options.z);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, obj.material->diffuse->id);
  glUniform1i(obj.shader->uniform_tex_diffuse, 0);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, obj.material->normal->id);
  glUniform1i(obj.shader->uniform_tex_normal, 1);

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, obj.material->specular->id);
  glUniform1i(obj.shader->uniform_tex_specular, 2);

  glEnableVertexAttribArray(obj.shader->attrib_position);
  glBindBuffer(GL_ARRAY_BUFFER, obj.mesh->vertex_buffer);
  glVertexAttribPointer(obj.shader->attrib_position, 3, GL_FLOAT, GL_FALSE, 0,
                        0);

  glEnableVertexAttribArray(obj.shader->attrib_uv);
  glBindBuffer(GL_ARRAY_BUFFER, obj.mesh->uv_buffer);
  glVertexAttribPointer(obj.shader->attrib_uv, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glEnableVertexAttribArray(obj.shader->attrib_normal);
  glBindBuffer(GL_ARRAY_BUFFER, obj.mesh->normal_buffer);
  glVertexAttribPointer(obj.shader->attrib_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glEnableVertexAttribArray(obj.shader->attrib_tangent);
  glBindBuffer(GL_ARRAY_BUFFER, obj.mesh->tangent_buffer);
  glVertexAttribPointer(obj.shader->attrib_tangent, 3, GL_FLOAT, GL_FALSE, 0,
                        0);

  glEnableVertexAttribArray(obj.shader->attrib_bitangent);
  glBindBuffer(GL_ARRAY_BUFFER, obj.mesh->bitangent_buffer);
  glVertexAttribPointer(obj.shader->attrib_bitangent, 3, GL_FLOAT, GL_FALSE, 0,
                        0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.mesh->element_buffer);

  glDrawElements(GL_TRIANGLES, obj.mesh->indices.size(), GL_UNSIGNED_SHORT, 0);

  glDisableVertexAttribArray(obj.shader->attrib_position);
  glDisableVertexAttribArray(obj.shader->attrib_uv);
  glDisableVertexAttribArray(obj.shader->attrib_normal);
  glDisableVertexAttribArray(obj.shader->attrib_tangent);
  glDisableVertexAttribArray(obj.shader->attrib_bitangent);
  glUseProgram(0);
}
}  // namespace spare
