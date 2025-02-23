#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "src/containers/dyn_arr.h"
#include "src/mat4f.h"
#include "src/memory/arena_allocator.h"
#include "src/obj_reader.h"
#include "src/ppm.h"

typedef struct {
  Vec3f position;
  Vec3f up;
  Vec3f target;
  float fov;
} Camera;

int main(void) {
  uint8_t* mem_buff = VirtualAlloc(nullptr, 1024 * 1024 * 8, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  Arena arena = arena_init(mem_buff, 1024 * 1024 * 8);

  constexpr uint32_t width = 512;
  constexpr uint32_t height = 512;
  constexpr size_t pixel_buff_len = sizeof(Color) * width * height;
  Color* restrict pixels = arena_alloc(&arena, pixel_buff_len);

  const Mat4f projection = mat4f_projection(90.0f, 16.0f / 9.0f, 0.01f, 1000.0f);

  const Mesh testing = obj_read(&arena, "C:\\Users\\Okharev\\CLionProjects\\SkratchRast\\assets\\teapot.obj");


  // FILE* file_ptr = fopen("C:\\Users\\Okharev\\CLionProjects\\SkratchRast\\file.ppm", "w+");
//
  // fprintf(file_ptr, "P3\n");
  // fprintf(file_ptr, "%d %d\n", width, height);
  // fprintf(file_ptr, "%d\n", 255);
//
  // for (int i = 0; i < width * height; ++i) {
  //   fprintf(file_ptr, "%d %d %d\n", (int)pixels[i].r, pixels[i].g, pixels[i].b);
  // }
//
  // fclose(file_ptr);

  return 0;
}