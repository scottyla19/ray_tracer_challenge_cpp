#include <iostream>
#include <typeinfo>
#include <cmath>

#include "Transform.h"
#include "../primitives/constants.h"

Translation::Translation(double x, double y, double z): Matrix(4,4){
    m_data[3] = x;
    m_data[7] = y;
    m_data[11] = z;
}

Scaling::Scaling(double x, double y, double z): Matrix(4,4){
    m_data[0] = x;
    m_data[5] = y;
    m_data[10] = z;
}

Rotation::Rotation(char axis, double radians): Matrix(4,4){
    switch (axis){
        case 'x':
            m_data[5] = cos(radians);
            m_data[6] = -sin(radians);
            m_data[9] = sin(radians);
            m_data[10] = cos(radians);
            break;
        case 'y':
            m_data[0] = cos(radians);
            m_data[2] = sin(radians);
            m_data[8] = -sin(radians);
            m_data[10] = cos(radians);
            break;
        case 'z':
            m_data[0] = cos(radians);
            m_data[1] = -sin(radians);
            m_data[4] = sin(radians);
            m_data[5] = cos(radians);
            break;
        default:
            m_data[5] = cos(radians);
            m_data[6] = -sin(radians);
            m_data[9] = sin(radians);
            m_data[10] = cos(radians);
    }
}

Shearing::Shearing(double xy, double xz, double yx, double yz, double zx, double zy): Matrix(4,4){
    m_data[1] = xy;
    m_data[2] = xz;
    m_data[4] = yx;
    m_data[6] = yz;
    m_data[8] = zx;
    m_data[9] = zy;
}

Matrix view_transform(Point from , Point to, Vector up)
{
    Vector forward = (to - from).normalize();
    Vector up_n = up.normalize();
    Vector left = cross(forward, up_n);
    Vector true_up = cross(left, forward);
    std::vector<double> data {left.x(), left.y(), left.z(), 0.0,
                              true_up.x(), true_up.y(), true_up.z(), 0.0,
                              -forward.x(), -forward.y(), -forward.z(), 0.0,
                              0,0,0,1};
    Matrix orientation = Matrix(4, 4, data);
    return orientation * Translation(-from.x(), -from.y(), -from.z());
}
