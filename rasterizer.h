#ifndef RASTERIZER_H_INCLUDED
#define RASTERIZER_H_INCLUDED

#include "myvector.h"
#include "tgaimage.h"
#include "culling_clipping.h"
#include "initialize.h"

void bresenham(vector2d v1, vector2d v2, TGAImage &image, TGAColor color);

void scanLine(vector2d v1, vector2d v2, vector2d v3, TGAImage &image, TGAColor color);
void baryCentric(vector3d v1, vector3d v2, vector3d v3, TGAImage &image, TGAColor color, float intensity, int* zbuffer, model m, int cnt);

#endif // RASTERIZER_H_INCLUDED
