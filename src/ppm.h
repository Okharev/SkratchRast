#ifndef PPM_H
#define PPM_H

#include <stddef.h>
#include <stdint.h>

#include "memory/arena_allocator.h"

typedef enum Format { P3, P6 } Format;

typedef union Color {
    struct {
        // Named struct for direct access
        uint8_t r, g, b, a;
    };

    uint8_t v[4]; // Array representation
} Color;

typedef struct PPMFile {
    Format format;
    uint32_t width, height;
    uint8_t color_depth;
    Color *pixel_buff;
} PPMFile;

PPMFile *init_file(Arena *arena, Format format, uint32_t width, uint32_t height);

void write_file(const PPMFile *restrict file, const char *restrict path);

void clear_pixel_buff(const PPMFile *restrict buffer, Color color);

void set_pixel(const PPMFile *restrict file, uint32_t widthPos, uint32_t heightPos, Color color);

void draw_line(const PPMFile *restrict file, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Color color);

#endif
