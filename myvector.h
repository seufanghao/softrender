#ifndef MYVECTOR_H
#define MYVECTOR_H

class vector2d
{
public:
    vector2d();
    vector2d(int a, int b);
    vector2d(const vector2d &vec2);

    vector2d operator+(const vector2d &vec2);
    vector2d operator-(const vector2d &vec2);
    vector2d operator=(const vector2d &vec2);

    int x;
    int y;

private:

};

class vector2f
{
public:
    vector2f();
    vector2f(double a, double b);
    vector2f(const vector2f &vec2);

    vector2f operator+(const vector2f &vec2);
    vector2f operator-(const vector2f &vec2);
    vector2f operator=(const vector2f &vec2);

    double x;
    double y;

private:

};


// 3 dimensional vector
class vector3f
{
public:
    vector3f(double a, double b, double c);

    vector3f(const vector3f &vec3);

    vector3f operator-(const vector3f &vec3);

    double x;
    double y;
    double z;
};
class vector3d
{
public:
    vector3d(int a, int b, int c);

    vector3d(const vector3d &vec3);
    vector3d operator-(const vector3d &vec3);

    int x;
    int y;
    int z;
};
vector3d cross(vector3d v1, vector3d v2);
vector3f cross(vector3f v1, vector3f v2);
double dot(vector3f v1, vector3f v2);

#endif // MYVECTOR_H
