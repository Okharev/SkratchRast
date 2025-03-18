#include <math.h>

#include "vec4f.h"

inline void vec4f_translate_inplace(Vec4f *restrict origin, const Vec4f *restrict const offset) {
    origin->x += offset->x;
    origin->y += offset->y;
    origin->z += offset->z;
}

inline void vec4f_scale_inplace(Vec4f *restrict origin, float const factor) {
    origin->x *= factor;
    origin->y *= factor;
    origin->z *= factor;
}

inline void vec4f_scale_dim_inplace(Vec4f *restrict origin, const Vec4f *restrict const scaler) {
    origin->x *= scaler->x;
    origin->y *= scaler->y;
    origin->z *= scaler->z;
}

inline Vec4f vec4f_translate(const Vec4f *restrict const origin, const Vec4f *restrict const offset) {
    const Vec4f res = (Vec4f){
        .x = origin->x + offset->x,
        .y = origin->y + offset->y,
        .z = origin->z + offset->z,
    };

    return res;
}

inline Vec4f vec4f_scale(const Vec4f *restrict origin, float const factor) {
    const Vec4f res = (Vec4f){
        .x = origin->x * factor,
        .y = origin->y * factor,
        .z = origin->z * factor,
    };

    return res;
}

inline Vec4f vec4f_scale_dim(const Vec4f *restrict const origin, const Vec4f *restrict const scaler) {
    const Vec4f res = (Vec4f){
        .x = origin->x * scaler->x,
        .y = origin->y * scaler->y,
        .z = origin->z * scaler->z,
    };

    return res;
}

inline float vec4f_distance(const Vec4f *restrict from, const Vec4f *restrict to) {
    return fabsf(sqrtf(powf(from->x - to->x, 2.0) + powf(from->y - to->y, 2.0) + powf(from->z - to->z, 2.0)));
}

inline Vec4f vec4f_zero() {
    const Vec4f res = (Vec4f){.x = 0.0, .y = 0.0, .z = 0.0};

    return res;
}

inline Vec4f vec4f_up() {
    const Vec4f res = (Vec4f){.x = 0.0, .y = 0.0, .z = 1.0};

    return res;
}

inline Vec4f vec4f_down() {
    const Vec4f res = (Vec4f){.x = 0.0, .y = 0.0, .z = -1.0};

    return res;
}

inline Vec4f vec4f_left() {
    const Vec4f res = (Vec4f){.x = 1.0, .y = 0.0, .z = 0.0};

    return res;
}

inline Vec4f vec4f_right() {
    const Vec4f res = (Vec4f){.x = -1.0, .y = 0.0, .z = 0.0};

    return res;
}

inline Vec4f vec4f_forward() {
    const Vec4f res = (Vec4f){.x = 0.0, .y = 1.0, .z = 0.0};

    return res;
}

inline Vec4f vec4f_backward() {
    const Vec4f res = (Vec4f){.x = 0.0, .y = -1.0, .z = 0.0};

    return res;
}
