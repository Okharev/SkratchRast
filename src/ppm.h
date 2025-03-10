#ifndef PPM_H
#define PPM_H

#include <stddef.h>
#include <stdint.h>

#include "containers/dyn_arr.h"

typedef enum { P3, P6 } Format;

typedef union {
  struct {  // Named struct for direct access
    uint8_t r, g, b, a;
  };

  uint8_t v[4];  // Array representation
} Color;

DYN_ARR_TYPE(Color, Color);

typedef struct {
  Format format;
  uint32_t width, height;
  uint8_t color_depth;
  ColorDynArr pixel_buff;
} PPMFile;

PPMFile init_file(Format format, uint32_t width, uint32_t height);
void clear_pixel_buff(const ColorDynArr* arr, Color color);
void set_pixel(const PPMFile* restrict file, uint32_t widthPos, uint32_t heightPos, Color color);
void draw_line(const PPMFile* file, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Color color);
void free_file(PPMFile* file);

#endif
