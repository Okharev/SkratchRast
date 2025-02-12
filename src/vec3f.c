#include "vec3f.h"
#include <math.h>

DYN_ARR_IMPL(Vec3f, Vec3f);

inline void vec3f_translate_inplace(Vec3f* origin, Vec3f* const offset) {
  origin->x += offset->x;
  origin->y += offset->y;
  origin->z += offset->z;
}

inline void vec3f_scale_inplace(Vec3f* origin, float const factor) {
  origin->x *= factor;
  origin->y *= factor;
  origin->z *= factor;
}

inline void vec3f_scale_dim_inplace(Vec3f* origin, Vec3f* const scaler) {
  origin->x *= scaler->x;
  origin->y *= scaler->y;
  origin->z *= scaler->z;
}

inline Vec3f vec3f_translate(Vec3f* const origin, Vec3f* const offset) {
  Vec3f res = (Vec3f){
      .x = origin->x + offset->x,
      .y = origin->y + offset->y,
      .z = origin->z + offset->z,
  };

  return res;
}

inline Vec3f vec3f_scale(Vec3f* origin, float const factor) {
  Vec3f res = (Vec3f){
      .x = origin->x * factor,
      .y = origin->y * factor,
      .z = origin->z * factor,
  };

  return res;
}

inline Vec3f vec3f_scale_dim(Vec3f* const origin, Vec3f* const scaler) {
  Vec3f res = (Vec3f){
      .x = origin->x * scaler->x,
      .y = origin->y * scaler->y,
      .z = origin->z * scaler->z,
  };

  return res;
}

inline float vec3f_distance(Vec3f* from, Vec3f* to) {
  return fabsf(sqrtf(powf(from->x - to->x, 2.0f) + powf(from->y - to->y, 2.0f) + powf(from->z - to->z, 2.0f)));
}

inline Vec3f vec3f_zero() {
  Vec3f res = (Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.0f};

  return res;
}

inline Vec3f vec3f_up() {
  Vec3f res = (Vec3f){.x = 0.0f, .y = 0.0f, .z = 1.0f};

  return res;
}

inline Vec3f vec3f_down() {
  Vec3f res = (Vec3f){.x = 0.0f, .y = 0.0f, .z = -1.0f};

  return res;
}

inline Vec3f vec3f_left() {
  Vec3f res = (Vec3f){.x = 1.0f, .y = 0.0f, .z = 0.0f};

  return res;
}

inline Vec3f vec3f_right() {
  Vec3f res = (Vec3f){.x = -1.0f, .y = 0.0f, .z = 0.0f};

  return res;
}

inline Vec3f vec3f_forward() {
  Vec3f res = (Vec3f){.x = 0.0f, .y = 1.0f, .z = 0.0f};

  return res;
}

inline Vec3f vec3f_backward() {
  Vec3f res = (Vec3f){.x = 0.0f, .y = -1.0f, .z = 0.0f};

  return res;
}