#include "spare/phiz/phiz_engine.h"

#include "spare/phiz/phiz_object.h"
#include "spare/spatial.h"

namespace spare {

PhizEngine::PhizEngine(entt::registry<> *registry) : registry(registry) {}

void PhizEngine::IntegrateRegistry(float delta) {
  auto view = registry->view<PhizObject, Spatial>();
  for (auto entity : view) {
    auto &spatial = view.get<Spatial>(entity);
    auto &phiz_object = view.get<PhizObject>(entity);

    phiz_object.Integrate(delta, spatial);
  }
}

}  // namespace spare
