#ifndef VEC4F_H
#define VEC4F_H

#include <stddef.h>
#include <stdint.h>

typedef union {
    struct {
        // Named struct for direct access
        float x, y, z, w;
    };

    float v[4]; // Array representation
} Vec4f;

void vec4f_translate_inplace(Vec4f *restrict origin, const Vec4f *restrict offset);

void vec4f_scale_inplace(Vec4f *restrict origin, float factor);

void vec4f_scale_dim_inplace(Vec4f *restrict origin, const Vec4f *restrict scaler);

Vec4f vec4f_translate(const Vec4f *restrict origin, const Vec4f *restrict offset);

Vec4f vec4f_scale(const Vec4f *restrict origin, float factor);

Vec4f vec4f_scale_dim(const Vec4f *restrict origin, const Vec4f *restrict scaler);

float vec4f_distance(const Vec4f *restrict from, const Vec4f *restrict to);

Vec4f vec4f_zero();

Vec4f vec4f_up();

Vec4f vec4f_down();

Vec4f vec4f_left();

Vec4f vec4f_right();

Vec4f vec4f_forward();

Vec4f vec4f_backward();

#endif
