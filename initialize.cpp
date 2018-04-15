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
    if(!src_tex.read_tga_file("african_head_diffuse.tga"))
    {
        cout << "error read texture file!" << endl;
    }
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
        // import vertex info to vert and vert_raw.
        if(line[0] == 'v' && line[1] == ' ')
        {
            int i = 2;
            int j = 0;
            vector<int> vert;
            vector<double> vert_raw;
            for(int k = 0; k < 3; k++)
            {
                while(line[i] != ' ' && line[i] != '\0')str[j++] = line[i++];
                str[j] = '\0';
                vert.push_back((int)((stof(str)+1.f)*500));
                vert_raw.push_back(stof(str));
                i++;
                j = 0;
            }
            src_vert.push_back(vector3d(vert[0], vert[1], vert[2]));
            src_vert_raw.push_back(vector3f(vert_raw[0], vert_raw[1], vert_raw[2]));
        }
        // import vertex index to vert_idx and texture index to tex_idx
        if(line[0] == 'f' && line[1] == ' ')
        {
            int i = 2;
            int j = 0;
            vector<int> vert_idx;
            vector<int> tex_location_idx;
            vector<int> unknown_idx;
            for(int k = 0; k < 3; k++)
            {
                while(line[i] != '/')str[j++] = line[i++];
                str[j] = '\0';
                vert_idx.push_back(stof(str));
                i++;
                j = 0;
                while(line[i] != '/')str[j++] = line[i++];
                str[j] = '\0';
                tex_location_idx.push_back(stof(str));
                i++;
                j = 0;
                while(line[i] != ' ' && line[i] != '\0')str[j++] = line[i++];
                str[j] = '\0';
                unknown_idx.push_back(stof(str));
                i++;
                j = 0;
            }
            //cout << tex_location_idx[0] << " " << tex_location_idx[1] << " " << tex_location_idx[2] << endl;
            src_vert_idx.push_back(vert_idx);
            src_tex_location_idx.push_back(tex_location_idx);
            // TODO: push unknown_idx to vector accordingly
            primitive_count++;
        }
        if(line[0] == 'v' && line[1] == 't')// check results
        {
            int i = 2;
            int j = 0;
            vector<int> tex_location;
            vector<double> tex_location_raw;
            for(int k = 0; k < 2; k++)
            {
                while(line[i] != ' ')str[j++] = line[i++];
                str[j] = '\0';
                tex_location.push_back((int)(stof(str)*1000));
                tex_location_raw.push_back(stof(str));
                i++;
                j = 0;
            }
            src_tex_location.push_back(vector2d(tex_location[0], tex_location[1]));
            src_tex_location_raw.push_back(vector2f(tex_location_raw[0], tex_location_raw[1]));
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

vector<vector2f> model::texture_location_raw(int idx)
{
    vector<vector2f> texture_location_raw;
    vector<int> texture_location_index = src_tex_location_idx[idx];
    int A_location_index = texture_location_index[0];
    int B_location_index = texture_location_index[1];
    int C_location_index = texture_location_index[2];
    cout <<"Index: " << A_location_index << " " << B_location_index << " " << C_location_index << endl;
    texture_location_raw.push_back(src_tex_location_raw[A_location_index]);
    texture_location_raw.push_back(src_tex_location_raw[B_location_index]);
    texture_location_raw.push_back(src_tex_location_raw[C_location_index]);
    cout << "Location_raw:=0 " << src_tex_location_raw[A_location_index].x << " " << src_tex_location_raw[B_location_index].x
    << " " << src_tex_location_raw[C_location_index].x << endl;
    cout << "Location:=0 " << src_tex_location[A_location_index].x << " " << src_tex_location[B_location_index].x
    << " " << src_tex_location[C_location_index].x << endl;

/*    vector2d A_location = src_tex_location[A_location_index];
    vector2d B_location = src_tex_location[B_location_index];
    vector2d C_location = src_tex_location[C_location_index];
    texture.push_back(src_tex.get(A_location.x, A_location.y));
    texture.push_back(src_tex.get(B_location.x, B_location.y));
    texture.push_back(src_tex.get(C_location.x, C_location.y));*/
    return texture_location_raw;
}
TGAColor model::texel(int x, int y)
{
    return src_tex.get(x, y);
}
