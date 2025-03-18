#ifndef QUATERNION_H
#define QUATERNION_H

#include "vec3f.h"

typedef struct Mat4f Mat4f;

typedef union Quaternion {
    struct {
        // Named struct for direct access
        float x, y, z, w;
    };

    float v[4]; // Array representation
} Quaternion;


Quaternion quat_look_at(const Vec3f *restrict origin, const Vec3f *restrict target, const Vec3f *restrict up);

Mat4f quat_to_mat4f(const Quaternion *restrict q);

#endif //QUATERNION_H
