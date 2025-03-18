#include "quaternion.h"
#include "mat4f.h"

Quaternion quat_look_at(const Vec3f *const restrict origin, const Vec3f *const restrict target,
                        const Vec3f *const restrict up) {
    // Calculate forward vector and normalize it.
    const Vec3f subbed = vec3f_substract(target, origin);
    const Vec3f forward = vec3f_normalize(&subbed);

    // Compute right vector: conventional cross product order.
    const Vec3f temp_right = vec3f_cross(&forward, up);
    const Vec3f right = vec3f_normalize(&temp_right);

    // Recompute up vector to ensure orthogonality.
    const Vec3f corrected = vec3f_cross(&right, &forward);

    // Build rotation matrix (assuming camera looks along -Z).
    const Mat4f view = (Mat4f){
        .mat = {
            {right.x, right.y, right.z, 0.0f},
            {corrected.x, corrected.y, corrected.z, 0.0f},
            {-forward.x, -forward.y, -forward.z, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };

    // Convert the rotation matrix to a quaternion.
    return mat4f_to_quat(&view);
}

Mat4f quat_to_mat4f(const Quaternion *const restrict q) {
    Mat4f m;

    // Precompute reused values.
    const float xx = q->x * q->x;
    const float yy = q->y * q->y;
    const float zz = q->z * q->z;
    const float xy = q->x * q->y;
    const float xz = q->x * q->z;
    const float yz = q->y * q->z;
    const float wx = q->w * q->x;
    const float wy = q->w * q->y;
    const float wz = q->w * q->z;

    // First row
    m.mat[0][0] = 1.0f - 2.0f * (yy + zz);
    m.mat[0][1] = 2.0f * (xy - wz);
    m.mat[0][2] = 2.0f * (xz + wy);
    m.mat[0][3] = 0.0f;

    // Second row
    m.mat[1][0] = 2.0f * (xy + wz);
    m.mat[1][1] = 1.0f - 2.0f * (xx + zz);
    m.mat[1][2] = 2.0f * (yz - wx);
    m.mat[1][3] = 0.0f;

    // Third row
    m.mat[2][0] = 2.0f * (xz - wy);
    m.mat[2][1] = 2.0f * (yz + wx);
    m.mat[2][2] = 1.0f - 2.0f * (xx + yy);
    m.mat[2][3] = 0.0f;

    // Fourth row (homogeneous coordinate)
    m.mat[3][0] = 0.0f;
    m.mat[3][1] = 0.0f;
    m.mat[3][2] = 0.0f;
    m.mat[3][3] = 1.0f;

    return m;
}
