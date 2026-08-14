#ifndef PURGEDGL_H
#define PURGEDGL_H

#include "defs.h"
#include "light.h"
#include "draw.h"
#include "video.h"
#include "3d.h"
#include "texture.h"

void PurgedGLInit
(
    GLContext *ctx,
    DWORD *fb,
    UINT *zbuff,
    DWORD w,
    DWORD h
);

#endif