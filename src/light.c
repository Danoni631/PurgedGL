#include "purgedgl.h"

static Vector3 vec_sub(Vector3 a, Vector3 b)
{
    return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static Vector3 vec_cross(Vector3 a, Vector3 b)
{
    return (Vector3)
    {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

static Vector3 vec_normalize(Vector3 v)
{
    float length_sq = v.x * v.x + v.y * v.y + v.z * v.z;
    if (length_sq <= 0.00001f) return (Vector3){0, 0, 0};

    float x2 = length_sq * 0.5f;
    float y = length_sq;
    int32_t i = *(int32_t*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (1.5f - (x2 * y * y));

    return (Vector3){v.x * y, v.y * y, v.z * y};
}

static float vec_dot(Vector3 a, Vector3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

void PurgedGLSetLightDir
(
    GLContext *ctx,
    float x, float y, float z
)
{
    Vector3 light = {x, y, z};
    ctx->light_dir = vec_normalize(light);
}