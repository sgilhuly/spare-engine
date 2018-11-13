#pragma once

#include <vector>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "glm/glm.hpp"

#include "spare/go/go_tree.h"
#include "spare/phiz/phiz_engine.h"
#include "spare/resource_loader.h"
#include "spare/spatial.h"

namespace spare {
class Engine : public GoTree {
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
  PhizEngine phiz_engine;
  ResourceLoader resources;
  SDL_Window *window = NULL;
  SDL_GLContext context;
  glm::vec4 options;

  int width;
  int height;
  bool paused = false;
};
}  // namespace spare
