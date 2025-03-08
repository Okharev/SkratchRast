#include "vec3f.h"
#include <math.h>

DYN_ARR_IMPL(Vec3f, Vec3f);

inline void vec3f_translate_inplace(Vec3f* origin, const Vec3f* const offset) {
  origin->x += offset->x;
  origin->y += offset->y;
  origin->z += offset->z;
}

inline void vec3f_scale_inplace(Vec3f* origin, float const factor) {
  origin->x *= factor;
  origin->y *= factor;
  origin->z *= factor;
}

inline void vec3f_scale_dim_inplace(Vec3f* origin, const Vec3f* const scaler) {
  origin->x *= scaler->x;
  origin->y *= scaler->y;
  origin->z *= scaler->z;
}

inline Vec3f vec3f_translate(const Vec3f* const origin, const Vec3f* const offset) {
  const Vec3f res = (Vec3f){
      .x = origin->x + offset->x,
      .y = origin->y + offset->y,
      .z = origin->z + offset->z,
  };

  return res;
}

inline Vec3f vec3f_scale(const Vec3f* origin, float const factor) {
  const Vec3f res = (Vec3f){
      .x = origin->x * factor,
      .y = origin->y * factor,
      .z = origin->z * factor,
  };

  return res;
}

inline Vec3f vec3f_scale_dim(const Vec3f* const origin, const Vec3f* const scaler) {
  const Vec3f res = (Vec3f){
      .x = origin->x * scaler->x,
      .y = origin->y * scaler->y,
      .z = origin->z * scaler->z,
  };

  return res;
}

inline float vec3f_distance(const Vec3f* from, const Vec3f* to) {
  return fabsf(sqrtf(powf(from->x - to->x, 2.0f) + powf(from->y - to->y, 2.0f) + powf(from->z - to->z, 2.0f)));
}

inline Vec3f vec3f_zero() {
  const Vec3f res = (Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.0f};

  return res;
}

inline Vec3f vec3f_up() {
  const Vec3f res = (Vec3f){.x = 0.0f, .y = 0.0f, .z = 1.0f};

  return res;
}

inline Vec3f vec3f_down() {
  const Vec3f res = (Vec3f){.x = 0.0f, .y = 0.0f, .z = -1.0f};

  return res;
}

inline Vec3f vec3f_left() {
  const Vec3f res = (Vec3f){.x = 1.0f, .y = 0.0f, .z = 0.0f};

  return res;
}

inline Vec3f vec3f_right() {
  const Vec3f res = (Vec3f){.x = -1.0f, .y = 0.0f, .z = 0.0f};

  return res;
}

inline Vec3f vec3f_forward() {
  const Vec3f res = (Vec3f){.x = 0.0f, .y = 1.0f, .z = 0.0f};

  return res;
}

inline Vec3f vec3f_backward() {
  const Vec3f res = (Vec3f){.x = 0.0f, .y = -1.0f, .z = 0.0f};

  return res;
}

void vec3f_print(const Vec3f* restrict vec) {
  // clang-format off
  printf(
      "|%.1f, %.1f, %.1f|\n",
      vec->x, vec->y, vec->z
  );
  // clang-format on
}