#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ppm.h"

DYN_ARR_IMPL(Color, Color);

inline void clear_pixel_buff(ColorDynArr* arr, Color color) {
#pragma omp parallel for schedule(static, 16)
  for (size_t i = 0; i < arr->size; ++i) {
    arr->data[i] = color;
  }
}

static inline void set_pixel(PPMFile* file, uint32_t widthPos, uint32_t heightPos, Color color) {
  file->pixel_buff.data[(file->width * heightPos) + widthPos] = color;
}

void draw_line(PPMFile* file, uint32_t x0, uint32_t y0, uint32_t const x1, uint32_t const y1, Color const color) {
  int32_t dx = abs(x1 - x0);
  int32_t dy = -abs(y1 - y0);

  int32_t error = dx + dy;

  int8_t sy = (y0 < y1) ? 1 : -1;
  int8_t sx = (x0 < x1) ? 1 : -1;

  while (1) {
    set_pixel(file, x0, y0, color);
    if (x0 == x1 && y0 == y1)
      break;
    int32_t e2 = 2 * error;
    if (e2 >= dy) {
      error += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      error += dx;
      y0 += sy;
    }
  }
}

inline PPMFile init_file(Format format, uint32_t width, uint32_t height) {
  PPMFile file = (PPMFile){
      .format = format,
      .width = width,
      .height = height,
      .color_depth = 255,
      .pixel_buff = ColorDynArr_init(width * height),
  };

  Color white = {255, 255, 255, 255};

  for (uint32_t i = 0; i < width * height; ++i) {
    ColorDynArr_pushback(&file.pixel_buff, white);
  }

  return file;
}

inline void free_file(PPMFile* file) {
  ColorDynArr_free(&file->pixel_buff);
}
