#ifndef VEC3F_H
#define VEC3F_H

#include <stddef.h>
#include <stdint.h>

#include "containers/dyn_arr.h"

typedef struct {
  float x, y, z;
} Vec3f;

DYN_ARR_TYPE(Vec3f, Vec3f);

void vec3f_translate_inplace(Vec3f* origin, const Vec3f* offset);
void vec3f_scale_inplace(Vec3f* origin, float factor);
void vec3f_scale_dim_inplace(Vec3f* origin, const Vec3f* scaler);

Vec3f vec3f_translate(const Vec3f* origin, const Vec3f* offset);
Vec3f vec3f_scale(const Vec3f* origin, float factor);
Vec3f vec3f_scale_dim(const Vec3f* origin, const Vec3f* scaler);

float vec3f_distance(const Vec3f* from, const Vec3f* to);

Vec3f vec3f_zero();
Vec3f vec3f_up();
Vec3f vec3f_down();
Vec3f vec3f_left();
Vec3f vec3f_right();
Vec3f vec3f_forward();
Vec3f vec3f_backward();

void vec3f_print(const Vec3f* vec);

#endif
