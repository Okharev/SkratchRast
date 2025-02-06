#include <stdlib.h>
#include <string.h>

#include "ppm.h"

DYN_ARR_IMPL(Color, Color);

inline void clear_pixel_buff(ColorDynArr* arr, Color color) {
  for (size_t i = 0; i < arr->size; ++i) {
    arr->data[i] = color;
  }
}

static inline void set_pixel(PPMFile* file, uint32_t widthPos, uint32_t heightPos, Color color) {
  file->pixel_buff.data[(file->width * heightPos) + widthPos] = color;
}

inline void draw_line(PPMFile* file, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Color color) {
  int m_new = 2 * (y2 - y1);
  int slope_error_new = m_new - (x2 - x1);

  for (int x = x1, y = y1; x <= x2; x++) {
    set_pixel(file, x, y, color);

    slope_error_new += m_new;

    if (slope_error_new >= 0) {
      y++;
      slope_error_new -= 2 * (x2 - x1);
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
