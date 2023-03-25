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
void Tuple::operator*( double s){
    m_x *= s;
    m_y *= s;
    m_z *= s;
    m_w *= s;
}
void Tuple::operator/( double s){
    m_x /= s;
    m_y /= s;
    m_z /= s;
    m_w /= s;
}
Tuple Tuple::normalize(){
    double d = magnitude();
    return Vector(x()/d, y()/d, z()/d);
}
double Tuple::magnitude(){
    return std::sqrt(std::pow(x(),2) + std::pow(y(),2) + std::pow(z(),2) + std::pow(w(),2));
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


// Vector operator-(const Point& t1, const Point& t2){
//     double x = t1.x() - t2.x();
//     double y = t1.y() - t2.y();
//     double z = t1.z() - t2.z();
//     double w = t1.w() - t2.w();
//     return Vector(x,y,z);
// }


// double Vector::magnitude(){
//     return std::sqrt(std::pow(x(),2) + std::pow(y(),2) + std::pow(z(),2) + std::pow(w(),2));
// }
// Vector Vector::normalize(){
//     double d = magnitude();
//     return Vector(x()/d, y()/d, z()/d);
// }
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





// TEST_CASE("test with w=1 is a point") {
//     Tuple a {Tuple(4.3, -4.2, 3.1,1.0)};
//     CHECK(typeid(a) == typeid(Tuple));
//     CHECK(floatEqual(a.x(),4.3));
//     CHECK(floatEqual(a.y(), -4.2));
//     CHECK(floatEqual(a.z() , 3.1));
//     CHECK(floatEqual(a.w()  , 1.0));
// }

// TEST_CASE("test point creates tuple w=1") {
//     Point a {Point(4.0, -4.0, 3.0)};
//     CHECK(typeid(a) == typeid(Point));
//     CHECK(dynamic_cast<Tuple*>(&a));
//     CHECK(floatEqual(a.x(),4.0));
//     CHECK(floatEqual(a.y(), -4.0));
//     CHECK(floatEqual(a.z() , 3.0));
//     CHECK(floatEqual(a.w()  , 1.0));
// }

// TEST_CASE("test vector creates tuple w=0") {
//     Vector a {Vector(4.0, -4.0, 3.0)};
//     CHECK(typeid(a) == typeid(Vector));
//     CHECK(dynamic_cast<Tuple*>(&a));
//     CHECK(floatEqual(a.x(),4.0));
//     CHECK(floatEqual(a.y(), -4.0));
//     CHECK(floatEqual(a.z() , 3.0));
//     CHECK(floatEqual(a.w()  , 0.0));
// }

// TEST_CASE("adding two tuples") {
//     Tuple a {Tuple(3, -2, 5, 1)};
//     Tuple b {Tuple(-2, 3, 1, 0)};
//     CHECK(a + b == Tuple(1, 1, 6, 1));

// }

// TEST_CASE("subracting two points") {
//     Point a {Point(3, 2,1)};
//     Point b {Point(5,6,7)};
//     CHECK(a - b == Vector(-2,-4,-6));
// }
// TEST_CASE("subracting vector from point") {
//     Point a {Point(3, 2,1)};
//     Vector b {Vector(5,6,7)};
//     CHECK(a - b == Point(-2,-4,-6));
// }

// TEST_CASE("negating a tuple") {
//     Tuple a {Tuple(1, -2, 3, -4)};
//     CHECK(-a == Tuple(-1, 2, -3, 4));

// }
// TEST_CASE("multiplying tuple and scalar") {
//     Tuple a {Tuple(1, -2, 3, -4)};
//     a *3.5;
//     CHECK(a == Tuple(3.5, -7, 10.5, -14));
// }

// TEST_CASE("multiplying tuple by fraction") {
//     Tuple a {Tuple(1, -2, 3, -4)};
//     a *0.5;
//     CHECK(a == Tuple(0.5, -1, 1.5, -2));
// }
// TEST_CASE("dividing tuple by fraction") {
//     Tuple a {Tuple(1, -2, 3, -4)};
//     a / 2;
//     CHECK(a == Tuple(0.5, -1, 1.5, -2));
// }

// TEST_CASE("magnitude of vector") {
//     Vector a {Vector(1,0,0)};
//     CHECK(a.magnitude() == 1);
//     Vector b {Vector(0,1,0)};
//     CHECK(b.magnitude() == 1);
//     Vector c {Vector(0,0,1)};
//     CHECK(c.magnitude() == 1);
//     Vector d {Vector(1,2,3)};
//     CHECK(floatEqual(d.magnitude(), std::sqrt(14)));
//     Vector e {Vector(-1,-2,-3)};
//     CHECK(floatEqual(e.magnitude(), std::sqrt(14)));
// }

// TEST_CASE("normalizing vectors"){
//     Vector a {Vector(4,0,0)};
//     CHECK(a.normalize() == Vector(1,0,0));
//     Vector b {Vector(1,2,3)};
//     CHECK(b.normalize() == Vector(1/std::sqrt(14),2/std::sqrt(14),3/std::sqrt(14)));
//     Vector norm = b.normalize();
//     CHECK(floatEqual(norm.magnitude() , 1));
// }

// TEST_CASE("dot product"){
//     Vector a {Vector(1,2,3)};
//     Vector b {Vector(2,3,4)};
//     CHECK(floatEqual(dot(a,b), 20));
// }

// TEST_CASE("cross product"){
//     Vector a {Vector(1,2,3)};
//     Vector b {Vector(2,3,4)};
//     CHECK(cross(a,b) == Vector(-1,2,-1));
//     CHECK(cross(b,a) == Vector(1,-2,1));

// }
