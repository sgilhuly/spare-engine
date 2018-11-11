#pragma once

#include "entt/entt.hpp"

namespace spare {

class PhizEngine {
 public:
  PhizEngine(entt::registry<> *registry);

  void IntegrateRegistry(float delta);

 private:
  entt::registry<> *registry;
};

}  // namespace spare
