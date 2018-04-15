#include "initialize.h"
#include <fstream>
#include <iostream>
using namespace std;

double stof(char* str)
{
    if(str == NULL)return 0;
    double high = 0;
    double low = 0;
    char *p = str;
    bool negative = 0;
    if(*p == '-'){ negative = 1; p++; }
    while(*p != '\0')
    {
        if(*p == '.'){ p++; break; }
        high = high * 10 + (*p - '0');
        p++;
    }
    double base = 10;
    while(*p != '\0')
    {
        low = low + (*p - '0')/base;
        base *= 10;
        p++;
    }
    if(negative)return (0 - high - low);
    else return (high + low);
}

model::model(const char* filename)
{
    primitive_count = 0;
    ifstream in;
    in.open(filename);
    if(in.fail())
    {
        cout << "Fail to open src.txt!" << endl;
        return;
    }
    string line;
    while(!in.eof())
    {
        getline(in, line);
        char str[256];
        double v[3] = {0};
        // import vertex info to vert and vert_raw.
        if(line[0] == 'v' && line[1] == ' ')
        {
            int i = 2;
            int j = 0;
            int cnt = 0;
            while(1)
            {
                if(line[i] != ' ' && line[i] != '\0')
                {
                    str[j] = line[i];
                    j++;
                }
                else
                {
                    str[j] = '\0';
                    v[cnt++] = stof(str);
                    j = 0;
                    if(line[i] == '\0')break;
                }
                i++;
            }
//            cout << v[0] << " " << v[1] << " " << v[2] << endl;
            vector3d vec3((int)((v[0]+1.f)*500), (int)((v[1]+1.f)*500), (int)((v[2]+1.f)*500));
            src_vert.push_back(vec3);
            vector3f vec3f(v[0], v[1], v[2]);
            src_vert_raw.push_back(vec3f);
        }
        // import vertex index to vert_idx and texture index to tex_idx
        if(line[0] == 'f' && line[1] == ' ')
        {
            int i = 1;
            int j = 0;
            int cnt = 0;
            bool start = 0;
            while(1)
            {
                if(line[i] == ' ')start = 1;
                else if(start)
                {
                    if(line[i] == '/')
                    {
                        str[j] = '\0';
                        v[cnt++] = stof(str);
                        start = 0;
                        j = 0;
                    }
                    else
                    {
                        str[j++] = line[i];
                    }
                }
                if(line[i] == '\0')break;
                i++;
            }
//            cout << v[0] << " " << v[1] << " " << v[2] << endl;
            vector<int> vec;
            vec.push_back(v[0]);
            vec.push_back(v[1]);
            vec.push_back(v[2]);
            src_vert_idx.push_back(vec);
            primitive_count++;
        }
        else continue;
    }
    in.close();
}
vector<vector3d> model::vertex(int idx)
{
    vector<vector3d> vertex;
    vector<int> vertice_index = src_vert_idx[idx];
    int A_index = vertice_index[0];
    int B_index = vertice_index[1];
    int C_index = vertice_index[2];
    vertex.push_back(src_vert[A_index-1]);
    vertex.push_back(src_vert[B_index-1]);
    vertex.push_back(src_vert[C_index-1]);
    return vertex;
}
vector<vector3f> model::vertex_raw(int idx)
{
    vector<vector3f> vertex_raw;
    vector<int> vertice_index = src_vert_idx[idx];
    int A_index = vertice_index[0];
    int B_index = vertice_index[1];
    int C_index = vertice_index[2];
    vertex_raw.push_back(src_vert_raw[A_index-1]);
    vertex_raw.push_back(src_vert_raw[B_index-1]);
    vertex_raw.push_back(src_vert_raw[C_index-1]);
    return vertex_raw;
}
/*vector2d model::texelLocation(int tex_idx)
{
    return tex[tex_location_idx-1];
}
vector3f model::texelLocation_raw(int tex_idx)
{
    return tex_location_raw[tex_location_idx-1];
}*/
vector<TGAColor> model::texture(int idx)
{
    vector<TGAColor> texture;
    vector<int> texture_location_index = src_tex_location_idx[idx];
    int A_location_index = texture_location_index[0];
    int B_location_index = texture_location_index[1];
    int C_location_index = texture_location_index[2];
    vector2d A_location = src_tex_location[A_location_index];
    vector2d B_location = src_tex_location[B_location_index];
    vector2d C_location = src_tex_location[C_location_index];
    texture.push_back(src_tex.get(A_location.x, A_location.y));
    texture.push_back(src_tex.get(B_location.x, B_location.y));
    texture.push_back(src_tex.get(C_location.x, C_location.y));
    return texture;
}
/*
vector<int> model::verticeIndex(int idx)
{
    return vert_idx[idx];
}
vector<int> model::texelLocationIndex(int idx)
{
    return tex_location_idx[idx];
}*/
