#include "spare/camera.h"

#include <cmath>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

const float mouse_x_speed = 0.5f;
const float mouse_y_speed = 0.5f;
const float camera_distance = 10.0f;
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
  int state = SDL_GetRelativeMouseState(&x, &y);

  if (state) {
    rotation += x * mouse_x_speed * delta;
    rotation = std::fmod(rotation, 2 * pi);
    pitch += y * mouse_y_speed * delta;
    pitch = std::fmin(std::fmax(pitch, -pi / 3), pi / 3);
  }

  float cam_x = -sin(rotation) * cos(pitch) * camera_distance;
  float cam_y = sin(pitch) * camera_distance;
  float cam_z = cos(rotation) * cos(pitch) * camera_distance;

  view = glm::lookAt(glm::vec3(cam_x, cam_y, cam_z), glm::vec3(0, 0, 0),
                     glm::vec3(0, 1, 0));

  // Position a light on the camera.
  light_position = glm::vec3(cam_x, cam_y, cam_z);
}

void Camera::Draw(const Drawable &drawable, const Spatial &spatial,
                  const glm::vec4 &options) {
  glUseProgram(drawable.shader->id);

  glm::mat4 mvp = projection * view * spatial.transform;
  glm::mat3 mv = glm::mat3(view * spatial.transform);
  glUniformMatrix4fv(drawable.shader->uniform_m, 1, GL_FALSE,
                     &spatial.transform[0][0]);
  glUniformMatrix4fv(drawable.shader->uniform_v, 1, GL_FALSE, &view[0][0]);
  glUniformMatrix3fv(drawable.shader->uniform_mv, 1, GL_FALSE, &mv[0][0]);
  glUniformMatrix4fv(drawable.shader->uniform_mvp, 1, GL_FALSE, &mvp[0][0]);
  glUniform3f(drawable.shader->uniform_light_position, light_position.x,
              light_position.y, light_position.z);
  glUniform4f(drawable.shader->uniform_lighting_options, options.x, options.y,
              options.z, options.w);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, drawable.material->diffuse->id);
  glUniform1i(drawable.shader->uniform_tex_diffuse, 0);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, drawable.material->normal->id);
  glUniform1i(drawable.shader->uniform_tex_normal, 1);

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, drawable.material->rad->id);
  glUniform1i(drawable.shader->uniform_tex_rad, 2);

  glEnableVertexAttribArray(drawable.shader->attrib_position);
  glBindBuffer(GL_ARRAY_BUFFER, drawable.mesh->vertex_buffer);
  glVertexAttribPointer(drawable.shader->attrib_position, 3, GL_FLOAT, GL_FALSE,
                        0, 0);

  glEnableVertexAttribArray(drawable.shader->attrib_uv);
  glBindBuffer(GL_ARRAY_BUFFER, drawable.mesh->uv_buffer);
  glVertexAttribPointer(drawable.shader->attrib_uv, 2, GL_FLOAT, GL_FALSE, 0,
                        0);

  glEnableVertexAttribArray(drawable.shader->attrib_normal);
  glBindBuffer(GL_ARRAY_BUFFER, drawable.mesh->normal_buffer);
  glVertexAttribPointer(drawable.shader->attrib_normal, 3, GL_FLOAT, GL_FALSE,
                        0, 0);

  glEnableVertexAttribArray(drawable.shader->attrib_tangent);
  glBindBuffer(GL_ARRAY_BUFFER, drawable.mesh->tangent_buffer);
  glVertexAttribPointer(drawable.shader->attrib_tangent, 3, GL_FLOAT, GL_FALSE,
                        0, 0);

  glEnableVertexAttribArray(drawable.shader->attrib_bitangent);
  glBindBuffer(GL_ARRAY_BUFFER, drawable.mesh->bitangent_buffer);
  glVertexAttribPointer(drawable.shader->attrib_bitangent, 3, GL_FLOAT,
                        GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable.mesh->element_buffer);

  glDrawElements(GL_TRIANGLES, drawable.mesh->indices.size(), GL_UNSIGNED_SHORT,
                 0);

  glDisableVertexAttribArray(drawable.shader->attrib_position);
  glDisableVertexAttribArray(drawable.shader->attrib_uv);
  glDisableVertexAttribArray(drawable.shader->attrib_normal);
  glDisableVertexAttribArray(drawable.shader->attrib_tangent);
  glDisableVertexAttribArray(drawable.shader->attrib_bitangent);
  glUseProgram(0);
}

}  // namespace spare
