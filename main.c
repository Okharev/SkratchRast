#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdalign.h>
#include <stdlib.h>

#include "src/containers/dyn_arr.h"
#include "src/helpers.h"
#include "src/mat4f.h"
#include "src/ppm.h"
#include "src/vec3f.h"
#include "src/vec4f.h"

typedef struct {
  uint16_t x1, x2;
  uint16_t y1, y2;
  Color color;
} Line;

DYN_ARR_TYPE(Line, Line)
DYN_ARR_IMPL(Line, Line)

int main(void) {
  const Mat4f test1 = mat4f_identity();
  const Mat4f test2 = mat4f_identity();

  Mat4f res;

  mat4f_multiply_out(&test1, &test2, &res);

  Mat4f projection = mat4f_projection(1.2f, 16.0f / 9.0f, 0.3f, 1000.0f);

  printf("%llu", __alignof(Mat4f));

  return 0;
}