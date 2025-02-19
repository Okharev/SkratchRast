#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
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
  // FILE* file_ptr;
  // file_ptr = fopen("C:\\Users\\Okharev\\CLionProjects\\SkratchRast\\file.ppm", "w+");
  //
  // PPMFile file = init_file(P3, 2560, 1440);
  //
  // LineDynArr vec = LineDynArr_init(1024 * 1024 * 64);
  //
  // #pragma omp parallel for schedule(static, 16)
  // for (int i = 0; i < 1024 * 1024 * 64; ++i) {
  //   vec.data[i] =
  //       (Line){.x1 = rand() % (file.width - 1), .x2 = rand() % (file.width - 1), .y1 = rand() % (file.height - 1), .y2 = rand() % (file.height - 1), .color = (Color){.r = rand() % (255 - 1), .g = rand() % (255 - 1), .b = rand() % (255 - 1), .a = 255}};
  // }
  //
  // #pragma omp parallel for schedule(static, 16)
  // for (int i = 0; i < 1024 * 1024 * 64; ++i) {
  //   draw_line(&file, vec.data[i].x1, vec.data[i].y1, vec.data[i].x2, vec.data[i].y2, vec.data[i].color);
  // }
  //
  // fprintf(file_ptr, "P3\n");
  // fprintf(file_ptr, "%d %d\n", file.width, file.height);
  // fprintf(file_ptr, "%d\n", file.color_depth);
  // for (int i = 0; i < file.pixel_buff.size; ++i) {
  //   fprintf(file_ptr, "%d %d %d\n", (int)file.pixel_buff.data[i].r, (int)file.pixel_buff.data[i].g, (int)file.pixel_buff.data[i].b);
  // }
  //
  // fclose(file_ptr);

  Vec4f player = (Vec4f){ 1.0f, 1.0f, -5.0f, 1.0f };
  Mat4f cam = mat4f_projection(90.0f, 1.0f, 10.0f, 1.0f);

  Vec4f final = mat4f_apply_projection(&cam, &player);

  printf("%.2f, %.2f, %.2f, %.2f\n", final.x, final.y, final.z, final.w);

  return 0;
}