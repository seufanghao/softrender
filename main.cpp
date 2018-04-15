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
    vector2d v1(200, 800);
    vector2d v2(400, 500);
    vector2d v3(700, 600);
//    bresenham(v1, v2, image, white);
//    bresenham(v1, v3, image, white);
//    bresenham(v2, v3, image, white);
//    scanLine(v1, v2, v3, image, white);
//    baryCentric(v1, v2, v3, image, red);

    model m1("src.txt");
    cout << "primitive num = " << m1.primitive_count << endl;
    vector3f lightdir(0.f, 0.f, 1.f);
    for(int i = 0; i < m1.primitive_count; i++)
    {
        // back-face culling
        vector<vector3f> triangle_raw = m1.vertex_raw(i);
        double intensity = backfaceCulling(triangle_raw[0], triangle_raw[1], triangle_raw[2], lightdir);
        if(intensity < 0)continue;

//        vector3d v4(m1.vertice(m1.index(i)[0]).x, m1.vertice(m1.index(i)[0]).y, m1.vertice(m1.index(i)[0]).z);
//        vector3d v5(m1.vertice(m1.index(i)[1]).x, m1.vertice(m1.index(i)[1]).y, m1.vertice(m1.index(i)[1]).z);
//        vector3d v6(m1.vertice(m1.index(i)[2]).x, m1.vertice(m1.index(i)[2]).y, m1.vertice(m1.index(i)[2]).z);
        vector<vector3d> triangle = m1.vertex(i);

        // rasterization and set depth buffer
        baryCentric(triangle[0], triangle[1], triangle[2], image, red, intensity, zbuffer);
//        bresenham(v4, v5, image, red);
//        bresenham(v4, v6, image, red);
//        bresenham(v5, v6, image, red);
//        scanLine(v4, v5, v6, image, white);
    }

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

