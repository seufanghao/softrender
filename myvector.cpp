#include "myvector.h"
#include <iostream>
using namespace std;

vector2d::vector2d():x(0),y(0)
{
}
vector2d::vector2d(int a, int b)
{
    x = a;
    y = b;
}
vector2d::vector2d(const vector2d &vec2)
{
    x = vec2.x;
    y = vec2.y;
}
vector2d vector2d::operator+(const vector2d &vec2)
{
    this->x = x + vec2.x;
    this->y = y + vec2.y;
    return *this;
}
vector2d vector2d::operator-(const vector2d &vec2)
{
    this->x = x - vec2.x;
    this->y = y - vec2.y;
    return *this;
}
vector2d vector2d::operator=(const vector2d &vec2)
{
    this->x = vec2.x;
    this->y = vec2.y;
    return *this;
}

vector3f::vector3f(double a, double b, double c)
{
    x = a;
    y = b;
    z = c;
}
vector3f::vector3f(const vector3f &vec3)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
}
vector3f vector3f::operator-(const vector3f &vec3)
{
    x = x - vec3.x;
    y = y - vec3.y;
    z = z - vec3.z;
    return *this;
}
vector3d::vector3d(int a, int b, int c)
{
    x = a;
    y = b;
    z = c;
}
vector3d::vector3d(const vector3d &vec3)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
}
vector3d vector3d::operator-(const vector3d & vec3)
{
    x = x - vec3.x;
    y = y - vec3.y;
    z = z - vec3.z;
    return *this;
}
vector3d cross(vector3d v1, vector3d v2)
{
    return vector3d(v1.y*v2.z-v2.y*v1.z, v1.z*v2.x-v2.z*v1.x, v1.x*v2.y-v2.x*v1.y);
}
vector3f cross(vector3f v1, vector3f v2)
{
    return vector3f(v1.y*v2.z-v2.y*v1.z, v1.z*v2.x-v2.z*v1.x, v1.x*v2.y-v2.x*v1.y);
}
double dot(vector3f v1, vector3f v2)
{
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}
