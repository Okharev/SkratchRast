#ifndef VEC3F_H
#define VEC3F_H

#include <stddef.h>
#include <stdint.h>

#include "containers/dyn_arr.h"

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

void vec3f_translate_inplace(Vec3f *restrict origin, const Vec3f *restrict offset);

void vec3f_scale_inplace(Vec3f *restrict origin, float factor);

void vec3f_scale_dim_inplace(Vec3f *restrict origin, const Vec3f *restrict scaler);

Vec3f vec3f_cross(const Vec3f *restrict vec_one, const Vec3f *restrict vec_two);

Vec3f vec3f_normalize(const Vec3f *restrict vec);

Vec3f vec3f_translate(const Vec3f *restrict origin, const Vec3f *restrict offset);

Vec3f vec3f_scale(const Vec3f *restrict origin, float factor);

Vec3f vec3f_scale_dim(const Vec3f *restrict origin, const Vec3f *restrict scaler);

Vec3f vec3f_substract(const Vec3f *restrict first, const Vec3f *restrict sec);

Vec3f vec3f_add(const Vec3f *restrict first, const Vec3f *restrict sec);

float vec3f_distance(const Vec3f *restrict from, const Vec3f *restrict to);

Vec3f vec3f_zero();

Vec3f vec3f_up();

Vec3f vec3f_down();

Vec3f vec3f_left();

Vec3f vec3f_right();

Vec3f vec3f_forward();

Vec3f vec3f_backward();

void vec3f_print(const Vec3f *restrict vec);

#endif
