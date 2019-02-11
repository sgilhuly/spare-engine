#include "spare/engine.h"

#include <cstdio>
#include <iostream>
#include <string>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "stb_image.h"

#include "spare/go/camera.h"
#include "spare/go/camera_arm.h"
#include "spare/go/go.h"
#include "spare/go/mesh.h"
#include "spare/go/rotator.h"
#include "spare/phiz/phiz_object.h"
#include "spare/resource_loader.h"
#include "spare/spatial.h"

using std::cout;
using std::endl;

namespace spare {
Engine::Engine(int width, int height) : width(width), height(height) {}

int Engine::OnExecute() {
  if (!OnInit()) {
    return -1;
  }

  SDL_Event event;
  int this_time = 0;
  int last_time = SDL_GetTicks();
  float delta = 0;

  int ticks = 0;
  float total_time = 0;

  while (running) {
    this_time = SDL_GetTicks();
    delta = (this_time - last_time) / 1000.0f;
    last_time = this_time;

    while (SDL_PollEvent(&event)) {
      OnEvent(event);
    }
    OnLoop(delta);
    OnRender(delta);

    ticks++;
    total_time += delta;
    if (total_time >= 0.25f) {
      char title[64];
      snprintf(title, sizeof(title), "Spare Engine - %0.2f FPS",
               ticks / total_time);
      SDL_SetWindowTitle(window, title);

      ticks = 0;
      total_time = 0;
    }
  }

  OnCleanup();

  return 0;
}

bool Engine::OnInit() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    cout << "Could not initialize SDL: " << SDL_GetError() << endl;
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  window = SDL_CreateWindow("Spare Engine", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (window == NULL) {
    cout << "Could not create window: " << SDL_GetError() << endl;
    return false;
  }

  context = SDL_GL_CreateContext(window);
  if (context == NULL) {
    cout << "Could not create OpenGL context: " << SDL_GetError() << endl;
    return false;
  }

  glewExperimental = GL_TRUE;
  GLenum glew_error;
  if ((glew_error = glewInit()) != GLEW_OK) {
    cout << "Error initializing GLEW: " << glewGetErrorString(glew_error)
         << endl;
  }

  if (SDL_GL_SetSwapInterval(1) < 0) {
    cout << "Warning: Unable to set VSync: " << SDL_GetError() << endl;
  }

  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor(0.1f, 0.2f, 0.3f, 1);

  // Configure stb
  stbi_set_flip_vertically_on_load(true);

  // TODO: fix this with proper scene loading
  MeshData *pillar_mesh = resources.GetMesh("stuff/cylinder.obj");
  Material *bricks_mat = resources.GetMaterial(
      "stuff/test/test_diffuse.png", "stuff/test/test_normal.png",
      "stuff/test/test_rad.png", "stuff/basic_lighting");
  MeshData *axes_mesh = resources.GetMesh("stuff/axes.obj");
  Material *rgb_mat = resources.GetMaterial(
      "stuff/rgb/rgb_diffuse.png", "stuff/rgb/rgb_normal.png",
      "stuff/rgb/rgb_rad.png", "stuff/basic_lighting");
  Go *go;
  Go *rotator;

  for (int i = 0; i < 4; ++i) {
    int x = i % 2;
    int z = i / 2;
    go = new Mesh(this, pillar_mesh, bricks_mat);
    rotator = new Rotator(this, glm::radians(90.0f * i), glm::vec3(0, 1, 0));
    rotator->SetPosition(glm::vec3(x * 4 - 2, 0, z * 4 - 2));
    rotator->AddChild(go);
    root->AddChild(rotator);
  }

  go = new Mesh(this, axes_mesh, rgb_mat);
  root->AddChild(go);

  Go *camera_arm = new CameraArm(this);
  root->AddChild(camera_arm);

  Go *camera = new Camera(this, width, height, 60.0f, 0.1f, 100.0f);
  camera->SetPosition(glm::vec3(0, 0, -12));
  camera_arm->AddChild(camera);

  options = glm::vec4(1, 1, 1, 1);

  return true;
}

void Engine::OnEvent(const SDL_Event &event) {
  switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          running = false;
          break;

        case SDLK_1:
          options.x = options.x > 0.5f ? 0 : 1;
          break;

        case SDLK_2:
          options.y = options.y > 0.5f ? 0 : 1;
          break;

        case SDLK_3:
          options.z = options.z > 0.5f ? 0 : 1;
          break;

        case SDLK_4:
          options.w = options.w > 0.5f ? 0 : 1;
          break;

        case SDLK_SPACE:
          paused = !paused;
          break;
      }
      break;
  }
}

void Engine::OnLoop(float delta) {
  if (!paused) {
    UpdateTree(delta);
  }
}

void Engine::OnRender(float delta) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  DrawTree();

  SDL_GL_SwapWindow(window);
}

void Engine::OnCleanup() {
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_Quit();
}
}  // namespace spare
