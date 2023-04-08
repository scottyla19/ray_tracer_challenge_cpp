#include "Shape.h"

Shape::Shape(): m_origin{Point(0,0,0)}, m_transform{Matrix(4,4)}, m_material{Material()}
{
}

Vector Shape::normal_at(const Point& p)const{
    Matrix t = m_transform.inverse();
//    std::cout << t << std::endl;
    Point object_point = t * p;
    Vector object_normal = object_point - m_origin;
    Vector world_normal = t.transpose() * object_normal;
    world_normal.setW(0.0);
    world_normal = world_normal.normalize();
//    Vector& n_ref = world_normal;
    return world_normal;
}

bool operator==(const Shape& s1, const Shape& s2){
   return (s1.getMaterial() == s2.getMaterial() && s1.getOrigin() == s2.getOrigin() && s1.getTransform() == s2.getTransform());
}

Sphere::Sphere(Point origin, double radius):   m_radius{radius}
{
    m_id = s_id++;
    m_origin = origin;
}

Sphere::Sphere():  m_radius{ 1.0}
{
    m_id = s_id++;
     m_origin = Point(0,0,0);
}

std::ostream& operator<< (std::ostream& out, const Shape& shape){
    out << "id: " << shape.getID() << " origin: " << shape.getOrigin() <<
    " material: " << shape.getMaterial() << " transform: " << shape.getTransform() << std::endl;
    return out;
}







