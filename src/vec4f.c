#include <math.h>

#include "vec4f.h"
#include "containers/dyn_arr.h"

DYN_ARR_IMPL(Vec3f, Vec3f);

inline void vec4f_translate_inplace(Vec4f* origin, Vec4f* const offset) {
  origin->x += offset->x;
  origin->y += offset->y;
  origin->z += offset->z;
}

inline void vec4f_scale_inplace(Vec4f* origin, float const factor) {
  origin->x *= factor;
  origin->y *= factor;
  origin->z *= factor;
}

inline void vec4f_scale_dim_inplace(Vec4f* origin, Vec4f* const scaler) {
  origin->x *= scaler->x;
  origin->y *= scaler->y;
  origin->z *= scaler->z;
}

inline Vec4f vec4f_translate(Vec4f* const origin, Vec4f* const offset) {
  Vec4f res = (Vec4f){
      .x = origin->x + offset->x,
      .y = origin->y + offset->y,
      .z = origin->z + offset->z,
  };

  return res;
}

inline Vec4f vec4f_scale(Vec4f* origin, float const factor) {
  Vec4f res = (Vec4f){
      .x = origin->x * factor,
      .y = origin->y * factor,
      .z = origin->z * factor,
  };

  return res;
}

inline Vec4f vec4f_scale_dim(Vec4f* const origin, Vec4f* const scaler) {
  Vec4f res = (Vec4f){
      .x = origin->x * scaler->x,
      .y = origin->y * scaler->y,
      .z = origin->z * scaler->z,
  };

  return res;
}

inline float vec4f_distance(Vec4f* from, Vec4f* to) {
  return fabsf(sqrtf(powf(from->x - to->x, 2.0) + powf(from->y - to->y, 2.0) + powf(from->z - to->z, 2.0)));
}

inline Vec4f vec4f_zero() {
  Vec4f res = (Vec4f){.x = 0.0, .y = 0.0, .z = 0.0};

  return res;
}

inline Vec4f vec4f_up() {
  Vec4f res = (Vec4f){.x = 0.0, .y = 0.0, .z = 1.0};

  return res;
}

inline Vec4f vec4f_down() {
  Vec4f res = (Vec4f){.x = 0.0, .y = 0.0, .z = -1.0};

  return res;
}

inline Vec4f vec4f_left() {
  Vec4f res = (Vec4f){.x = 1.0, .y = 0.0, .z = 0.0};

  return res;
}

inline Vec4f vec4f_right() {
  Vec4f res = (Vec4f){.x = -1.0, .y = 0.0, .z = 0.0};

  return res;
}

inline Vec4f vec4f_forward() {
  Vec4f res = (Vec4f){.x = 0.0, .y = 1.0, .z = 0.0};

  return res;
}

inline Vec4f vec4f_backward() {
  Vec4f res = (Vec4f){.x = 0.0, .y = -1.0, .z = 0.0};

  return res;
}