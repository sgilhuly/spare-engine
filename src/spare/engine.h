#pragma once

#include <vector>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "entt/entt.hpp"
#include "glm/glm.hpp"

#include "spare/camera.h"
#include "spare/resource_loader.h"
#include "spare/spatial.h"

namespace spare {
class Engine {
 public:
  Engine(int width, int height);
  int OnExecute();
  bool OnInit();
  void OnEvent(const SDL_Event &event);
  void OnLoop(float delta);
  void OnRender(float delta);
  void OnCleanup();

 private:
  bool running = true;
  Camera camera;
  ResourceLoader resources;
  SDL_Window *window = NULL;
  SDL_GLContext context;
  entt::registry<> registry;
  glm::vec3 options;

  int width;
  int height;
};
}  // namespace spare
