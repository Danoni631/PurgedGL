#include "../include/std.h"

#define PGL_TRIANGLES 0

typedef struct
{
    float x;
    float y;
    float z;
} Vector3;

typedef struct
{
    float m[4][4];
} Matrix4;

typedef struct
{
    DWORD *pixels;
    DWORD width;
    DWORD height;
} GLTexture;

typedef struct
{
    DWORD *color_buffer;
    DWORD *z_buffer;
    DWORD width;
    DWORD height;
    
    Matrix4 projection;
    Matrix4 modelview;
    DWORD current_color;
    
    GLTexture *current_texture;

    Vector3 vertex_queue[3];
    Vector3 vertex_queue_3d;
    int vertex_count;
    Vector3 light_dir;
    Vector3 world_queue[3];
} GLContext;

typedef struct
{
    float x, y, z;
    float u, v;
} Vertex;