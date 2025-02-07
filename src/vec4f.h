#ifndef VEC4F_H
#define VEC4F_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  float x, y, z, w;
} Vec4f;

void vec4f_translate_inplace(Vec4f* origin, Vec4f* const offset);
void vec4f_scale_inplace(Vec4f* origin, float const factor);
void vec4f_scale_dim_inplace(Vec4f* origin, Vec4f* const scaler);

Vec4f vec4f_translate(Vec4f* const origin, Vec4f* const offset);
Vec4f vec4f_scale(Vec4f* const origin, float const factor);
Vec4f vec4f_scale_dim(Vec4f* const origin, Vec4f* const scaler);

float vec4f_distance(Vec4f* from, Vec4f* to);

Vec4f vec4f_zero();
Vec4f vec4f_up();
Vec4f vec4f_down();
Vec4f vec4f_left();
Vec4f vec4f_right();
Vec4f vec4f_forward();
Vec4f vec4f_backward();

#endif
