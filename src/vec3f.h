#ifndef VEC3F_H
#define VEC3F_H

#include <stddef.h>
#include <stdint.h>

#include "containers/dyn_arr.h"

typedef struct {
  float x, y, z;
} Vec3f;

DYN_ARR_TYPE(Vec3f, Vec3f);

void vec3f_translate_inplace(Vec3f* origin, Vec3f* const offset);
void vec3f_scale_inplace(Vec3f* origin, float const factor);
void vec3f_scale_dim_inplace(Vec3f* origin, Vec3f* const scaler);

Vec3f vec3f_translate(Vec3f* const origin, Vec3f* const offset);
Vec3f vec3f_scale(Vec3f* const origin, float const factor);
Vec3f vec3f_scale_dim(Vec3f* const origin, Vec3f* const scaler);

float vec3f_distance(Vec3f* from, Vec3f* to);

Vec3f vec3f_zero();
Vec3f vec3f_up();
Vec3f vec3f_down();
Vec3f vec3f_left();
Vec3f vec3f_right();
Vec3f vec3f_forward();
Vec3f vec3f_backward();

#endif
