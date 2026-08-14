#include "purgedgl.h"
#include "pgl_math.h"
#include "light.h"

void PurgedGLModePerspective
(
    GLContext *ctx,
    float fov_deg,
    float aspect,
    float near, float far
)
{
    float f = 1.0f / fast_tan((fov_deg * 0.5f) * (3.1415926f / 180.0f));
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ctx->projection.m[i][j] = 0.0f;
        }
    }

    ctx->projection.m[0][0] = f / aspect;
    ctx->projection.m[1][1] = f;
    ctx->projection.m[2][2] = (far + near) / (near - far);
    ctx->projection.m[2][3] = (2.0f * far * near) / (near - far);
    ctx->projection.m[3][2] = -1.0f;
}

void PurgedGLVertex(GLContext *ctx, float x, float y, float z)
{
    Vector3 raw_v = {x, y, z};

    Vector3 world_v = mat_mul_vec(&ctx->modelview, raw_v);
    ctx->world_queue[ctx->vertex_count] = world_v;

    Vector3 proj_v = mat_mul_vec(&ctx->projection, world_v);
    ctx->vertex_queue[ctx->vertex_count++] = proj_v;

    if (ctx->vertex_count == 3)
    {
        Vector3 edge1 =
        vec_sub(ctx->world_queue[1], ctx->world_queue[0]);
        Vector3 edge2 =
        vec_sub(ctx->world_queue[2], ctx->world_queue[0]);
        
        Vector3 normal = vec_normalize(vec_cross(edge1, edge2));

        float intensity = -vec_dot(normal, ctx->light_dir);

        if (intensity < 0.0f) intensity = 0.0f;

        float ambient = 0.2f;
        float factor = ambient + intensity * (1.0f - ambient);
        if (factor > 1.0f) factor = 1.0f;

        BYTE r = (BYTE)(((ctx->current_color >> 16) & 0xFF) * factor);
        BYTE g = (BYTE)(((ctx->current_color >> 8)  & 0xFF) * factor);
        BYTE b = (BYTE)(((ctx->current_color)       & 0xFF) * factor);

        DWORD shaded_color = 0xFF000000 | (r << 16) | (g << 8) | b;
        DWORD original_color = ctx->current_color;
        ctx->current_color = shaded_color;

        draw_triangle_zbuff
        (
            ctx, ctx->vertex_queue[0],
            ctx->vertex_queue[1],
            ctx->vertex_queue[2]
        );

        ctx->current_color = original_color;
        ctx->vertex_count = 0;
    }
}