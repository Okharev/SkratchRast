#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "src/ppm.h"

int main(void) {
  PPMFile file = init_file(P3, 16, 16);

  draw_line(&file, 0, 0, 7, 7, (Color){255, 0, 0, 255});

  printf("P3\n");
  printf("%d %d\n", file.width, file.height);
  printf("%d\n", file.color_depth);
  for (int i = 0; i < file.pixel_buff.size; ++i) {
    printf("%d %d %d\n", (int)file.pixel_buff.data[i].r, (int)file.pixel_buff.data[i].g, (int)file.pixel_buff.data[i].b);
  }

  return 0;
}