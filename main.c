#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

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

typedef struct {
  uint16_t X;
  uint16_t Y;
} ScreenPos;

int main(void) {
  constexpr size_t size = 1024 * 1024 * 8;  // 8MB
  uint8_t* restrict mem_buff = malloc(size);
  Arena level_arena = arena_init(mem_buff, size);

  const PPMFile file = init_file(P3, 240, 135);
  clear_pixel_buff(&file.pixel_buff, (Color){0, 0, 0});

  const Mesh mesh = obj_read(&level_arena, "../assets/m4a1_s.obj");
  const Vec3f camera_pos = (Vec3f){.x = 10.0f, .y = 0.0f, .z = 15.0f};
  const Vec3f mesh_pos = (Vec3f){.x = 10.0f, .y = 0.0f, .z = 0.0f};

  const Mat4f proj = mat4f_projection(1.00472f, 16.0f / 9.0f, 0.0001f, 10000.0f);
  const Mat4f view = mat4f_translate(&(Vec3f){.x = -camera_pos.x, .y = -camera_pos.y, .z = -camera_pos.z});
  const Mat4f world = mat4f_translate(&mesh_pos);

  Mat4f vp, mvp;  // View-projection
  mat4f_multiply(&proj, &view, &vp);
  mat4f_multiply(&vp, &world, &mvp);

  for (size_t i = 0; i < mesh.total_vertices; ++i) {
    Vec4f out;
    mat4f_multiply_vec4f(&(Vec4f){.x = mesh.vertices[i].x, .y = mesh.vertices[i].y, .z = mesh.vertices[i].z, .w = 1.0f}, &out, &mvp);

    constexpr float EPSILON = 1e-6f;  // Very small tolerance number
    if (fabsf(out.w) <= EPSILON)
      continue;  // Skip unsafe divide by zero

    const float inv_w = 1.0f / out.w;
    const Vec3f ndc = {out.x * inv_w, out.y * inv_w, out.z * inv_w};

    // Clipping check: NDC must be between -1 and 1
    if (ndc.x < -1.0f || ndc.x > 1.0f || ndc.y < -1.0f || ndc.y > 1.0f || ndc.z < -1.0f || ndc.z > 1.0f)
      continue;

    const uint16_t screenX = (uint16_t)((ndc.x + 1.0f) * 0.5f * 240.0f);
    const uint16_t screenY = (uint16_t)((1.0f - ndc.y) * 0.5f * 135.0f);

    // Screen bounds check
    if (screenX >= 240 || screenY >= 135)
      continue;

    set_pixel(&file, screenX, screenY, (Color){255, 255, 255});
  }

  write_file(&file, "../image.ppm");

  return 0;
}