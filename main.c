#include <stdint.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

#include "src/mesh.h"
#include "src/memory/arena_allocator.h"
#include "src/camera.h"
#include "src/quaternion.h"

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

  Entity entity = (Entity) {
    .mesh = mesh_from_obj(&level_arena, "../../assets/ak47.obj"),
    .transform = (Transform){
      .SRT_mat = mat4f_identity(),
      .quaternion = quat_look_at(&(Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.0f }, &(Vec3f){.x = 0.0f, .y = 0.0f, .z = 1.0f }, &(Vec3f) { .x = 0.0f, .y = 1.0f, .z = 0.0f }),
      .scale = (Vec3f){.x = 1.0f, .y = 1.0f, .z = 1.0f},
      .position = (Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.0f },
      .is_dirty = true
    }
  };

  Camera cam = init_camera(
    (Vec3f){.x = 1.0f, .y = 1.0f, .z = 1.0f },
    quat_look_at(&(Vec3f){.x = 1.0f, .y = 1.0f, .z = 1.0f }, &(Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.0f }, &(Vec3f) { .x = 0.0f, .y = 1.0f, .z = 0.0f }),
    (Vec3f) { .x = 0.0f, .y = 1.0f, .z = 0.0f },
    40.0f,
    0.0001f,
    10000.0f,
    16.0f / 9.0f
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
    render_mesh(renderer, &cam, &entity);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    SDL_RenderPresent(renderer);

    SDL_UpdateWindowSurface(window);
    const Vec3f new_pos = (Vec3f) { .x = cam.transform.position.x + 0.001f, .y = cam.transform.position.y + 0.001f, .z = cam.transform.position.z + 0.001f };
    move_camera(&cam, &new_pos);

  }

  return 0;
}