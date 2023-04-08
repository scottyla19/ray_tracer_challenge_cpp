#pragma once
#include "Matrix.h"
#include "../primitives/Tuple.h"
#include "../primitives/constants.h"



class Translation: public Matrix{
private:
    double m_x;
    double m_y;
    double m_z;

public:
    Translation(double x, double y, double z);

    ~Translation() = default;
};

class Scaling: public Matrix{
private:
    double m_x;
    double m_y;
    double m_z;

public:
    Scaling(double x, double y, double z);

    ~Scaling() = default;
};

class Rotation: public Matrix{
private:
    double m_rads;
    char m_axis;

public:
    Rotation(char axis, double radians);

    ~Rotation() = default;
};

class Shearing: public Matrix{
private:
    double m_xy;
    double m_xz;
    double m_yx;
    double m_yz;
    double m_zx;
    double m_zy;

public:
    Shearing(double xy, double xz, double yx, double yz, double zx, double zy);

    ~Shearing() = default;
};

Matrix view_transform(Point from , Point to, Vector up);
