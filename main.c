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
  Vec3f rotation;  // Could represent Euler angles.
  Vec3f scale;
} Transform;

typedef struct {
  Vec3f position;
  Vec3f up;
  Vec3f target;
  float fov;
} Camera;

typedef struct {
  Mesh* mesh;
  Mat4f transform;
} Entity;

int main(void) {
  uint8_t* level_buff = VirtualAlloc(nullptr, 1024 * 1024 * 8, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  Arena level_arena = arena_init(level_buff, 1024 * 1024 * 8);

  Mesh mesh = obj_read(&level_arena, "C:\\Users\\Okharev\\CLionProjects\\SkratchRast\\assets\\teapot.obj");
  auto entity = (Entity){.mesh = &mesh, .transform = mat4f_identity()};

  const auto cameraPos = (Vec3f) { .x = 5.0f, .y = 5.0f, .z = 5.0f };

  // First, apply object transform
  const Mat4f object_transform = mat4f_translate(&(Vec3f) { .x = 1.0f, .y = 1.0f, .z = 1.0f });
  mat4f_multiply(&entity.transform, &object_transform, &entity.transform);

  // Then, apply the camera transformation LAST
  const Mat4f view_transform = mat4f_translate(&(Vec3f) { .x = -cameraPos.x, .y = -cameraPos.y, .z = -cameraPos.z });
  mat4f_multiply(&entity.transform, &view_transform, &entity.transform);

  for (size_t i = 0; i < 5; ++i) {
    Vec3f output;

    mat4f_multiply_vec3f(&mesh.vertices[i], &output, &entity.transform);
    vec3f_print(&output);
  }

  return 0;
}