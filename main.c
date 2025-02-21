#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "src/containers/dyn_arr.h"
#include "src/mat4f.h"
#include "src/helpers.h"
#include "src/ppm.h"
#include "src/memory/arena_allocator.h"



int main(void) {
  uint8_t trash = 4;
  uint8_t byte = 7;
  char tess[] = "sdfsdf\0";
  uint8_t buff[4096 * 4] = {};
  Arena arena = arena_init(&buff, sizeof(uint8_t) * 4096 * 4);

  Vec4f* vertices = arena_alloc(&arena, sizeof(Vec4f) * 32);

  for (int i = 0; i < 32; ++i) {
    Vec4f v;
    v.x = (float)i;
    v.y = (float)i;
    v.z = (float)i;
    v.w = 0.0f;
    vertices[i] = v;
  }

  Mat4f* transforms = arena_alloc(&arena, sizeof(Mat4f) * 4);

  for (int i = 0; i < 32; ++i) {
    transforms[i] = mat4f_identity();
  }

  return 0;
}