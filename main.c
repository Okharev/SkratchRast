#include <stdint.h>
#include <stdlib.h>
#include "src/mesh.h"
#include "src/memory/arena_allocator.h"
#include "src/camera.h"

#include <SDL3/SDL.h>

int main(void) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    perror("Failed to init SDL");
    exit(1);
  }

  SDL_Window* window = SDL_CreateWindow("Obj rendered", 480, 270, 0);
  if (window == nullptr) {
    perror("Failed to init window");
    exit(1);
  }

  SDL_Surface* surface = SDL_GetWindowSurface(window);
  SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface);
  if (renderer == nullptr) {
    perror("Failed to init renderer");
    exit(1);
  }

  constexpr size_t size = 1024 * 1024 * 1; // 1MB
  uint8_t* restrict mem_buff = malloc(size);
  Arena level_arena = arena_init(mem_buff, size);

  const Mesh* mesh = mesh_from_obj(&level_arena, "../../assets/teapot.obj");
  Camera cam = init_camera(
    (Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.0f },
    (Vec3f) { .x = 0.0f, .y = 1.0f, .z = 0.0f },
    (Vec3f) { .x = 0.0f, .y = 0.0f, .z = -1.0f },
    40.0f
  );

  while (true) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        return 0;
      }

      if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
        return 0;
      }
    }

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    render_mesh(renderer, &cam, mesh);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    SDL_RenderPresent(renderer);

    SDL_UpdateWindowSurface(window);

    cam.position.y += 0.00001f;
    cam.position.x += 0.00001f;
    cam.position.z += 0.00001f;
  }

  return 0;
}