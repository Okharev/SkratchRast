#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat4f.h"

typedef struct {
    Vec3f position;
    Vec3f quaternion;
    Vec3f scale;

    Mat4f SRT_mat;
    bool is_dirty;
} Transform;

void set_position(const Vec3f* restrict new_position, Transform* restrict transform);
void set_rotation(const Vec3f* restrict new_rotation, Transform* restrict transform);
void set_scale(const Vec3f* restrict new_scale, Transform* restrict transform);
const Mat4f* get_srt(Transform* restrict transform);

#endif //TRANSFORM_H
