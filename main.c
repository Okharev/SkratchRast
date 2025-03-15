#include <stdint.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "src/mesh.h"
#include "src/memory/arena_allocator.h"
#include "src/camera.h"
#include "src/ppm.h"

int main(void) {
  // constexpr size_t size = 1024 * 1024 * 1; // 1MB
  // uint8_t *restrict mem_buff = malloc(size);
  // Arena level_arena = arena_init(mem_buff, size);
  //
  // const PPMFile* file = init_file(&level_arena, P3, 480, 270);
  // clear_pixel_buff(file, (Color){0, 0, 0});
  //
  // const Mesh *mesh = mesh_from_obj(&level_arena, "../assets/karanbit.obj");
  // Camera cam = init_camera((Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.3f }, (Vec3f) { .x = 0.0f, .y = 1.0f, .z = 0.0f }, (Vec3f) { .x = 0.0f, .y = 0.0f, .z = 0.0f }, 40.0f);
  //
  // // TODO Refactor this to handle window buffers
  // uint16_t i = 0;
  // char line[32];
  // while (i != 10) {
  //     sprintf(line, "../image-%u.ppm", i);
  //
  //     render_mesh(&cam, mesh, file);
  //     write_file(file, line);
  //     clear_pixel_buff(file, (Color) { 0, 0, 0 });
  //
  //     cam.position.z += 1.0f;
  //     i++;
  // }
  //
  // arena_free_all(&level_arena);
  // free(mem_buff);

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
  uint8_t *restrict mem_buff = malloc(size);
  Arena level_arena = arena_init(mem_buff, size);

  const Mesh *mesh = mesh_from_obj(&level_arena, "../../assets/karanbit.obj");
  Camera cam = init_camera((Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.3f }, (Vec3f) { .x = 0.0f, .y = 1.0f, .z = 0.0f }, (Vec3f) { .x = 0.0f, .y = 0.0f, .z = 0.0f }, 40.0f);

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

    /* Got everything on rendering surface,
       now Update the drawing image on window screen */
    SDL_UpdateWindowSurface(window);

    cam.position.x -=0.0001f;
  }

  return 0;
}