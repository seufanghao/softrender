#include <iostream>
#include "culling_clipping.h"
#include <cmath>
using namespace std;

double backfaceCulling(vector3f v1, vector3f v2, vector3f v3, vector3f lightdir)
{
    vector3f va = v2 - v1;
    vector3f vb = v3 - v1;
    vector3f vc = cross(va, vb);
    double mod = (double)(vc.x*vc.x + vc.y*vc.y + vc.z*vc.z);
    vector3f vn(((double)vc.x)/sqrt(mod), ((double)vc.y)/sqrt(mod), ((double)vc.z)/sqrt(mod));

    double intensity = dot(vn, lightdir);
//    cout << "in function: " << vn.x << " " << vn.y << " " << vn.z << endl;
    return intensity;
}
