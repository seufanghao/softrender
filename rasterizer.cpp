#include "rasterizer.h"
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
    double delta = (double)(v2.y - v1.y) / (double)(v2.x - v1.x);
    int tmp_x = v1.x;
    int tmp_y = v1.y;
    double error = 0;
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
    double k1 = ((double)(v3.x - v1.x) / (double)(v3.y - v1.y));
    double k2 = ((double)(v2.x - v1.x) / (double)(v2.y - v1.y));
    double k3 = ((double)(v3.x - v2.x) / (double)(v3.y - v2.y));
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
void baryCentric(vector3d v1, vector3d v2, vector3d v3, TGAImage &image, TGAColor color, double intensity, int* zbuffer, model m, int cnt)
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
            double u = 1.f-((double)(res.x+res.y))/((double)res.z);
            double v = ((double)res.y)/((double)res.z);
            double w = ((double)res.x)/((double)res.z);
            if(u >= 0 && u <= 1 && v >= 0 && v <= 1 && w >= 0 && w <= 1)
            {
                vp.z = u*v1.z + v*v2.z + w*v3.z;
                if(vp.z > zbuffer[vp.x*1000+vp.y])
                {
                    zbuffer[vp.x*1000+vp.y] = vp.z;
                    //image.set(vp.x, vp.y, TGAColor(intensity*255, intensity*255, intensity*255, 255));
                    vector<vector2f> locations = m.texture_location_raw(cnt);
                    vector2d location((int)(1000*(locations[0].x+locations[1].x+locations[2].x)), (int)(1000*(locations[0].x+locations[1].x+locations[2].x)));
                    //cout << cnt << " " << locations[0].x << " " << locations[1].x << " " << locations[2].x << endl;
                    TGAColor c = m.texel(location.x, location.y);
                    image.set(vp.x, vp.y, c);
                }
            }
        }
    }
}
