#include "rasterizer.h"
#include <limits>
#include <iostream>
using namespace std;

void bresenham(vector2d v1, vector2d v2, TGAImage &image, TGAColor color)
{
    bool rotate = false;
    if(abs(v1.x - v2.x) < abs(v1.y - v2.y))
    {
        swap(v1.x, v1.y);
        swap(v2.x, v2.y);
        rotate = true;
    }
    if(v1.x > v2.x)
    {
        swap(v1.x, v2.x);
        swap(v1.y, v2.y);
    }
    float delta = (float)(v2.y - v1.y) / (float)(v2.x - v1.x);
    int tmp_x = v1.x;
    int tmp_y = v1.y;
    float error = 0;
    for(tmp_x = v1.x; tmp_x <= v2.x; tmp_x++)
    {
        error = error + delta;
        if(error > 1 || error < -1)
        {
            tmp_y += ((delta > 0)?1:-1);
            error += ((delta > 0)?-1:1);
        }
        if(rotate)
        {
            image.set(tmp_y, tmp_x, color);
        }
        else
        {
            image.set(tmp_x, tmp_y, color);
        }
    }
}

void scanLine(vector2d v1, vector2d v2, vector2d v3, TGAImage &image, TGAColor color)
{
    if(v1.y > v2.y){swap(v1.x, v2.x); swap(v1.y, v2.y);};
    if(v1.y > v3.y){swap(v1.x, v3.x); swap(v1.y, v3.y);};
    if(v2.y > v3.y){swap(v2.x, v3.x); swap(v2.y, v3.y);};
    float k1 = ((float)(v3.x - v1.x) / (float)(v3.y - v1.y));
    float k2 = ((float)(v2.x - v1.x) / (float)(v2.y - v1.y));
    float k3 = ((float)(v3.x - v2.x) / (float)(v3.y - v2.y));
    for(int y = v1.y; y <= v2.y; y++)
    {
        int x1 = v1.x + (y - v1.y) * k1;
        int x2 = v1.x + (y - v1.y) * k2;
        for(int x = min(x1, x2)+1; x <= max(x1, x2); x++)
        {
            image.set(x, y, color);
        }
    }
    for(int y = v3.y; y > v2.y; y--)
    {
        int x1 = v3.x + (y - v3.y) * k1;
        int x2 = v3.x + (y - v3.y) * k3;
        for(int x = min(x1, x2)+1; x <= max(x1, x2); x++)
        {
            image.set(x, y, color);
        }
    }
}
void baryCentric(vector3d v1, vector3d v2, vector3d v3, TGAImage &image, TGAColor color, float intensity, int* zbuffer, model m, int cnt)
{
    int min_x = min(min(v1.x, v2.x), v3.x);
    int max_x = max(max(v1.x, v2.x), v3.x);
    int min_y = min(min(v1.y, v2.y), v3.y);
    int max_y = max(max(v1.y, v2.y), v3.y);

    vector3d vp(0, 0, 0);
    for(vp.x = min_x; vp.x <= max_x; vp.x++)
    {
        for(vp.y = min_y; vp.y <= max_y; vp.y++)
        {
            vector3d vx(v2.x-v1.x, v3.x-v1.x, v1.x-vp.x);
            vector3d vy(v2.y-v1.y, v3.y-v1.y, v1.y-vp.y);
            vector3d res = cross(vx, vy);
            float u = 1.f-((float)(res.x+res.y))/((float)res.z);
            float v = ((float)res.y)/((float)res.z);
            float w = ((float)res.x)/((float)res.z);
            if(u >= 0 && u <= 1 && v >= 0 && v <= 1 && w >= 0 && w <= 1)
            {
                vp.z = u*v1.z + v*v2.z + w*v3.z;
                if(vp.z > zbuffer[vp.x*1000+vp.y])
                {
                    zbuffer[vp.x*1000+vp.y] = vp.z;

                    // flat shading
                    //image.set(vp.x, vp.y, TGAColor(intensity*255, intensity*255, intensity*255, 255));

                    // gouraud shading
                    vector3f lightdir(0.f, 0.f, 1.f);
                    vector<vector3f> normals = m.vertex_normal_raw(cnt);
                    // v1~normals[0], v3~normals[1], v2~normal[2]
                    float intensity_0 = dot(lightdir, normals[0]);
                    float intensity_1 = dot(lightdir, normals[1]);
                    float intensity_2 = dot(lightdir, normals[2]);
                    if(intensity_0 < 0)intensity_0 = 0;
                    if(intensity_1 < 0)intensity_1 = 0;
                    if(intensity_2 < 0)intensity_2 = 0;

                    TGAColor v1_color = TGAColor(255*intensity_0, 255*intensity_0, 255*intensity_0, 255);
                    TGAColor v2_color = TGAColor(255*intensity_1, 255*intensity_1, 255*intensity_1, 255);
                    TGAColor v3_color = TGAColor(255*intensity_2, 255*intensity_2, 255*intensity_2, 255);
                    unsigned char R = (u*v1_color.r + v*v2_color.r + w*v3_color.r);
                    //cout << "max of unsigned char is " << (int)numeric_limits<unsigned char>::max() << endl;
                    if(vp.x == 269 && vp.y == 739)
                    {
                        cout << "intensity= " << intensity_0 << " " << intensity_1 << " " << intensity_2 << endl;
                        cout << "u=" << u << " v=" << v << " w=" << w <<endl;
                        cout << "result = " << "u*v1_color.r=" << u*v1_color.r << " v*v2_color.r=" << v*v2_color.r << " w*v3_color.r=" << w*v3_color.r << endl;
                        cout << "color = " << (int)(u*v1_color.r + v*v2_color.r + w*v3_color.r) << endl;
                    }
                    //image.set(vp.x, vp.y, TGAColor(R, R, R, 255));

                    // phong shading
                    vector3f p_normal = normals[0]*u + normals[1]*v + normals[2]*w;
                    float p_intensity = dot(lightdir, p_normal);
                    if(p_intensity >= 0)image.set(vp.x, vp.y, TGAColor(255*p_intensity, 255*p_intensity, 255*p_intensity, 255));

                    // texture mapping
                    vector<vector2f> locations = m.texture_location_raw(cnt);
                    vector2f location = vector2f(1000*(u*locations[0].x + v*locations[1].x + w*locations[2].x),
                                         1000*(u*locations[0].y + v*locations[1].y + w*locations[2].y));
                    if(location.x - ((int)location.x) > 0.5)location.x = (int)(location.x) + 1;
                    if(location.y - ((int)location.y) > 0.5)location.y = (int)(location.y) + 1;
                    //cout << cnt << " " << locations[0].x << " " << locations[1].x << " " << locations[2].x << endl;
                    TGAColor c = m.texel(location.x, location.y);
                    //image.set(vp.x, vp.y, c);
                }
            }
        }
    }
}
