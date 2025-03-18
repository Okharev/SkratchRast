#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat4f.h"

typedef struct {
    Mat4f SRT_mat;
    Vec4f quaternion;
    Vec3f scale;
    Vec3f position;

    bool is_dirty;
} Transform;

void set_position(const Vec3f* restrict new_position, Transform* restrict transform);
void set_rotation(const Vec4f* restrict new_rotation, Transform* restrict transform);
void set_scale(const Vec3f* restrict new_scale, Transform* restrict transform);
const Mat4f* get_trs(Transform* restrict transform);

#endif //TRANSFORM_H
