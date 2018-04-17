#ifndef INITIALIZE_H_INCLUDED
#define INITIALIZE_H_INCLUDED

#include <vector>
#include "myvector.h"
#include "tgaimage.h"
using namespace std;

class model
{
public:
    model(const char* filename);

    vector<vector3f> vertex_raw(int idx);
    vector<vector3d> vertex(int idx);

    vector<vector2d> texture_location(int idx);
    vector<vector2f> texture_location_raw(int idx);
    TGAColor texel(int x, int y);

    vector<vector3f> vertex_normal_raw(int idx);

    int primitive_count;
private:
    // vertex attribute
    vector<vector<int>> src_vert_idx;
    vector<vector3d> src_vert;
    vector<vector3f> src_vert_raw;

    // texture
    vector<vector<int>> src_tex_location_idx;
    vector<vector2d> src_tex_location;
    vector<vector2f> src_tex_location_raw;

    TGAImage src_tex;

    // vertex normal
    vector<vector<int>> src_vert_normal_idx;
    vector<vector3f> src_vert_normal_raw;

};

#endif // INITIALIZE_H_INCLUDED
