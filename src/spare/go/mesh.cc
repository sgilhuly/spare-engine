#include "spare/go/mesh.h"
#include <iostream>

#include "GL/glew.h"
#include "SDL2/SDL.h"

namespace spare {

Mesh::Mesh(GoTree *tree, MeshData *mesh, Material *material)
    : Go(tree), mesh(mesh), material(material) {}

Mesh::~Mesh() {}

void Mesh::Draw(const glm::mat4 &projection, const glm::mat4 &view) {
  glUseProgram(material->shader->id);

  glm::mat4 mvp = projection * view * global_transform;
  glm::mat3 mv = glm::mat3(view * global_transform);
  glm::vec3 light_position = glm::vec3(0, 1, 0);
  glm::vec4 options = glm::vec4(1, 1, 1, 1);

  glUniformMatrix4fv(material->shader->uniform_m, 1, GL_FALSE,
                     &global_transform[0][0]);
  glUniformMatrix4fv(material->shader->uniform_v, 1, GL_FALSE, &view[0][0]);
  glUniformMatrix3fv(material->shader->uniform_mv, 1, GL_FALSE, &mv[0][0]);
  glUniformMatrix4fv(material->shader->uniform_mvp, 1, GL_FALSE, &mvp[0][0]);
  glUniform3f(material->shader->uniform_light_position, light_position.x,
              light_position.y, light_position.z);
  glUniform4f(material->shader->uniform_lighting_options, options.x, options.y,
              options.z, options.w);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, material->diffuse->id);
  glUniform1i(material->shader->uniform_tex_diffuse, 0);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, material->normal->id);
  glUniform1i(material->shader->uniform_tex_normal, 1);

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, material->rad->id);
  glUniform1i(material->shader->uniform_tex_rad, 2);

  glEnableVertexAttribArray(material->shader->attrib_position);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
  glVertexAttribPointer(material->shader->attrib_position, 3, GL_FLOAT,
                        GL_FALSE, 0, 0);

  glEnableVertexAttribArray(material->shader->attrib_uv);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->uv_buffer);
  glVertexAttribPointer(material->shader->attrib_uv, 2, GL_FLOAT, GL_FALSE, 0,
                        0);

  glEnableVertexAttribArray(material->shader->attrib_normal);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->normal_buffer);
  glVertexAttribPointer(material->shader->attrib_normal, 3, GL_FLOAT, GL_FALSE,
                        0, 0);

  glEnableVertexAttribArray(material->shader->attrib_tangent);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->tangent_buffer);
  glVertexAttribPointer(material->shader->attrib_tangent, 3, GL_FLOAT, GL_FALSE,
                        0, 0);

  glEnableVertexAttribArray(material->shader->attrib_bitangent);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->bitangent_buffer);
  glVertexAttribPointer(material->shader->attrib_bitangent, 3, GL_FLOAT,
                        GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->element_buffer);

  glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_SHORT, 0);

  glDisableVertexAttribArray(material->shader->attrib_position);
  glDisableVertexAttribArray(material->shader->attrib_uv);
  glDisableVertexAttribArray(material->shader->attrib_normal);
  glDisableVertexAttribArray(material->shader->attrib_tangent);
  glDisableVertexAttribArray(material->shader->attrib_bitangent);
  glUseProgram(0);
}

}  // namespace spare
