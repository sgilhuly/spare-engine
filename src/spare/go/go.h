#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace spare {

class GoTree;

class Go {
 public:
  Go(GoTree *tree);
  virtual ~Go();

  virtual void Update(float delta){};
  virtual void Draw(const glm::mat4 &projection, const glm::mat4 &view){};

  void AddChild(Go *child);
  void Detach();

  glm::vec3 ToGlobal(const glm::vec3 &point) const;

  void Traverse(float delta);
  void TraverseDraw(const glm::mat4 &projection, const glm::mat4 &view);

  void SetPosition(const glm::vec3 &p) {
    position = p;
    dirty = true;
  }
  void SetRotation(const glm::quat &r) {
    rotation = r;
    dirty = true;
  }
  void SetScale(const glm::vec3 &s) {
    scale = s;
    dirty = true;
  }
  void Translate(const glm::vec3 &t) {
    position += t;
    dirty = true;
  }
  void Rotate(const glm::quat &q) {
    rotation *= q;
    dirty = true;
  }

 protected:
  glm::vec3 position = glm::vec3();
  glm::quat rotation = glm::quat();
  glm::vec3 scale = glm::vec3(1);

  glm::mat4 global_transform;
  glm::mat4 local_transform;

  std::vector<Go *> children;
  Go *parent = nullptr;
  GoTree *tree = nullptr;

  bool dirty = true;
};

}  // namespace spare
