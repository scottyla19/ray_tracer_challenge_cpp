#include <iostream>
#include <typeinfo>
#include <cmath>

#include "Tuple.h"
#include "constants.h"



Tuple::Tuple(double x, double y, double z, double w)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
}


Tuple operator+(const Tuple& t1, const Tuple& t2){
    double x = t1.x() + t2.x();
    double y = t1.y() + t2.y();
    double z = t1.z() + t2.z();
    double w = t1.w() + t2.w();
    return Tuple(x,y,z,w);
}
bool operator==(const Tuple& t1, const Tuple& t2){
    return floatEqual(t1.x() , t2.x()) &&
    floatEqual(t1.y() , t2.y())&&
    floatEqual(t1.z() , t2.z()) &&
    floatEqual(t1.w() , t2.w());
}
//
//double Tuple::operator[]const(int i){
//    if (i == 0){
//        return m_x;
//    } else if (i == 1){
//        return m_y;
//    }else if (i == 2){
//        return m_z;
//    }else{
//        return m_w;
//    }
//
//}
Tuple operator-(const Tuple& t1, const Tuple& t2){
    double x = t1.x() - t2.x();
    double y = t1.y() - t2.y();
    double z = t1.z() - t2.z();
    double w = t1.w() - t2.w();
    return Tuple(x,y,z, w);
}
Tuple Tuple::operator- () const
{
    return { -m_x, -m_y, -m_z, -m_w };
}
void Tuple::set_index(int i, double value){
    if (i == 0){
        m_x = value;
    } else if (i == 1){
        m_y = value;
    }else if (i == 2){
        m_z = value;
    }else{
        m_w = value;
    }
}
Tuple Tuple::operator*( double s){
    m_x *= s;
    m_y *= s;
    m_z *= s;
    m_w *= s;
    return *this;
}
Tuple Tuple::operator/( double s){
    m_x /= s;
    m_y /= s;
    m_z /= s;
    m_w /= s;
    return *this;
}
Tuple Tuple::normalize(){
    double d = magnitude();
    return Vector(x()/d, y()/d, z()/d);
}
double Tuple::magnitude(){
    return std::sqrt(std::pow(x(),2) + std::pow(y(),2) + std::pow(z(),2) + std::pow(w(),2));
}
Vector& Vector::reflect(const Vector& normal) const{
    Vector n = normal;
    Vector result = *this - n * 2 * dot(*this, n) ;
    Vector& r = result;
    return r;
}

std::ostream& operator<< (std::ostream& out, const Tuple& tuple){
    out << "Tuple(" << tuple.x() << ", " << tuple.y() << ", " << tuple.z() << ", " << tuple.w() <<')';
    return out; // return s
}



Point::Point(double x, double y, double z):    Tuple{x, y, z, 1.0}
{
}
Point::Point(const Tuple& t = Tuple(0.0, 0.0, 0.0, 1.0)):
    Tuple(t.x(), t.y(), t.z(), 1.0)
{

}
Point::Point(): Tuple(0.0, 0.0, 0.0, 1.0)
{
}

Vector::Vector(double x, double y, double z):
    Tuple{x, y, z, 0.0}
{
}

Vector::Vector(const Tuple& t):
    Tuple(t.x(), t.y(), t.z(), 0.0)
{
}

Vector::Vector(): Tuple(0,0,0,0)
{
}


double dot(const Vector& v1, const Vector& v2){
    return (v1.x() * v2.x() +
            v1.y() * v2.y() +
            v1.z() * v2.z());
}
Tuple cross(const Vector& a, const Vector& b){
    return Vector(a.y()*b.z() - a.z()*b.y(),
                 a.z()*b.x() - a.x()*b.z(),
                 a.x()*b.y() - a.y()*b.x());
}



