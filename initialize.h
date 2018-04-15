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

    vector<TGAColor> texture(int idx);
    int primitive_count;
private:
    vector<vector<int>> src_vert_idx;
    vector<vector3d> src_vert;
    vector<vector3f> src_vert_raw;

    vector<vector<int>> src_tex_location_idx;
    vector<vector2d> src_tex_location;
    vector<vector2f> src_tex_location_raw;

    TGAImage src_tex;
};

#endif // INITIALIZE_H_INCLUDED
