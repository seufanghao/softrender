#include <iostream>
#include "tgaimage.h"
#include "myvector.h"

#include "initialize.h"
#include "rasterizer.h"

using namespace std;

const int width = 1000;
const int height = 1000;
static int zbuffer[1000*1000] = {0};
TGAImage image(width, height, TGAImage::RGB);
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor none  = TGAColor(0,   0,   0,   255);

int main()
{
    model m1("src.txt");
    cout << "primitive num = " << m1.primitive_count << endl;
    vector3f lightdir(0.f, 0.f, 1.f);
    for(int i = 0; i < m1.primitive_count; i++)
    {
        // back-face culling
        vector<vector3f> triangle_raw = m1.vertex_raw(i);
        float intensity = backfaceCulling(triangle_raw[0], triangle_raw[1], triangle_raw[2], lightdir);
        if(intensity < 0)continue;

        vector<vector3d> triangle = m1.vertex(i);

        // rasterization and set depth buffer
/*        if((triangle[0].x > 400 && triangle[0].x < 600)
           || (triangle[1].x > 400 && triangle[1].x < 600)
           || (triangle[2].x > 400 && triangle[2].x < 600))*/
        baryCentric(triangle[0], triangle[2], triangle[1], image, red, intensity, zbuffer, m1, i);
        //bresenham(vector2d(triangle[0].x, triangle[0].y), vector2d(triangle[0].x, triangle[0].y), image, red);
        //bresenham(vector2d(triangle[1].x, triangle[1].y), vector2d(triangle[1].x, triangle[1].y), image, red);
        //bresenham(vector2d(triangle[2].x, triangle[2].y), vector2d(triangle[2].x, triangle[2].y), image, red);
//        scanLine(v4, v5, v6, image, white);
    }

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

