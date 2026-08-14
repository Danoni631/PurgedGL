#include "purgedgl.h"

void PurgedGLInit
(
    GLContext *ctx,
    DWORD *fb,
    UINT *zbuff,
    DWORD w,
    DWORD h
)
{
    ctx->color_buffer = fb;
    ctx->z_buffer = zbuff;
    ctx->width = w;
    ctx->height = h;
    ctx->vertex_count = 0;
    ctx->current_color = 0xFFFFFFFF;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        { 
            ctx->modelview.m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}