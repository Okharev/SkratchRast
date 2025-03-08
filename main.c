#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "src/mat4f.h"
#include "src/memory/arena_allocator.h"
#include "src/obj_reader.h"

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

typedef struct {
  uint16_t X;
  uint16_t Y;
} ScreenPos;

Vec3f world_to_camera(const Camera* const restrict camera, const Vec3f* const restrict position) {
  Vec3f result;
  result.x = position->x - camera->position.x;
  result.y = position->y - camera->position.y;
  result.z = position->z - camera->position.z;
  return result;
}

int main(void) {
  constexpr size_t size = 1024 * 1024 * 8;  // 8MB
  size_t test = 15;
  uint8_t* restrict mem_buff = malloc(size);
  Arena level_arena = arena_init(mem_buff, size);

  Mesh mesh = obj_read(&level_arena, "../assets/teapot.obj");
  auto entity = (Entity){ .mesh = &mesh, .transform = mat4f_identity() };

  const auto cameraPos = (Vec3f) { .x = 5.0f, .y = 5.0f, .z = 5.0f };

  // First, apply object transform
  const Mat4f object_transform = mat4f_translate(&(Vec3f) { .x = 1.0f, .y = 1.0f, .z = 1.0f });
  mat4f_multiply(&entity.transform, &object_transform, &entity.transform);

  // Then, apply the camera transformation LAST
  const Mat4f view_transform = mat4f_translate(&(Vec3f) { .x = -cameraPos.x, .y = -cameraPos.y, .z = -cameraPos.z });
  mat4f_multiply(&entity.transform, &view_transform, &entity.transform);

  for (size_t i = 0; i < mesh.total_vertices; ++i) {
    Vec3f output;

    mat4f_multiply_vec3f(&mesh.vertices[i], &output, &entity.transform);

    printf("%f", output.x);
  }

  return 0;
}