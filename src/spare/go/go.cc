#include "spare/go/go.h"

#include <algorithm>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include "spare/go/go_tree.h"

namespace spare {

Go::Go(GoTree *tree) : tree(tree) {}

Go::~Go() {
  Detach();
  for (Go *go : children) {
    go->parent = nullptr;
    delete go;
  }
  children.clear();
}

void Go::AddChild(Go *child) {
  child->Detach();
  children.push_back(child);
  child->parent = this;
  child->dirty = true;
}

void Go::Detach() {
  if (parent) {
    std::remove(parent->children.begin(), parent->children.end(), this);
  }
  parent = nullptr;
}

glm::vec3 Go::ToGlobal(const glm::vec3 &point) const {
  return glm::vec3(global_transform * glm::vec4(point, 1));
}

void Go::Traverse(float delta) {
  // if (dirty) {
  //   local_transform = glm::translate(glm::toMat4(rotation), position);
  // }

  // if (parent) {
  //   if (dirty || parent->dirty) {
  //     global_transform = local_transform * parent->global_transform;
  //   }
  // } else if (dirty) {
  //   global_transform = local_transform;
  // }

  if (parent && parent->dirty) {
    global_transform = local_transform * parent->global_transform;
  }

  Update(delta);

  if (dirty) {
    local_transform = glm::translate(glm::toMat4(rotation), position);
    if (parent) {
      global_transform = local_transform * parent->global_transform;
    } else {
      global_transform = local_transform;
    }
  }

  for (Go *go : children) {
    go->Traverse(delta);
  }

  dirty = false;
}

void Go::TraverseDraw(const glm::mat4 &projection, const glm::mat4 &view) {
  Draw(projection, view);
  for (Go *go : children) {
    go->TraverseDraw(projection, view);
  }
}

}  // namespace spare
