#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ppm.h"

#include "memory/arena_allocator.h"

inline void clear_pixel_buff(const PPMFile* const restrict buffer, const Color color) {
  for (size_t i = 0; i < buffer->height * buffer->width; ++i) {
    buffer->pixel_buff[i] = color;
  }
}

inline void set_pixel(const PPMFile* const restrict file, const uint32_t widthPos, const uint32_t heightPos, const Color color) {
  file->pixel_buff[file->width * heightPos + widthPos] = color;
}

void draw_line(const PPMFile* restrict file, uint32_t x0, uint32_t y0, uint32_t const x1, uint32_t const y1, Color const color) {
  const int32_t dx = x1 - x0;
  const int32_t dy = -(y1 - y0);

  int32_t error = dx + dy;

  const int8_t sy = y0 < y1 ? 1 : -1;
  const int8_t sx = x0 < x1 ? 1 : -1;

  while (1) {
    set_pixel(file, x0, y0, color);
    if (x0 == x1 && y0 == y1)
      break;
    const int32_t e2 = 2 * error;
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

PPMFile* init_file(Arena* arena, const Format format, const uint32_t width, const uint32_t height) {
  PPMFile* file = arena_alloc(arena, sizeof(PPMFile));

  file->format = format;
  file->width = width;
  file->height = height;
  file->color_depth = 255;
  file->pixel_buff = arena_alloc(arena, width * height * sizeof(Color));

  for (uint32_t i = 0; i < width * height; ++i) {
    const Color white = {{255, 255, 255, 255}};
    file->pixel_buff[i] = white;
  }

  return file;
}

void write_file(const PPMFile* restrict file, const char* restrict path) {
  FILE* restrict image = fopen(path, "wb+");
  // TODO Make a parser to handle binary data
  fprintf(image, "P3\n%hu %hu\n255\n", file->width, file->height);

  for (uint32_t i = 0; i < file->width * file->height; ++i) {
    const Color pixel = file->pixel_buff[i];
    fprintf(image, "%u %u %u\n", pixel.r, pixel.g, pixel.b);
  }
}