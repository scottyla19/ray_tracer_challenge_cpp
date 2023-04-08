#include "Ray.h"
#include <iostream>
#include <cmath>

Ray::Ray(Point origin = Point(0,0,0), Vector direction = Vector(0,0,1))
{
    m_origin = origin;
    m_direction = direction;
}


Point Ray::position(double t){
    Point p = getOrigin() + (getDirection() * t);
    return p;
}

Ray Ray::transform(Matrix t){
    m_origin = t * m_origin;
    m_direction = t * m_direction;
    return *this;
}

IntersectList Ray::intersects(Shape s){
    Ray r2 = transform(s.getTransform().inverse());
    Vector sphere_to_ray = m_origin - s.getOrigin();
    double  a = dot(m_direction, m_direction);
    double b = 2 * dot(m_direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - 1.0;
    double discriminant =(b * b) - (4 * a * c);
    if (discriminant < 0){
        return IntersectList();
    }else{
        double t1 = (-b - sqrt(discriminant))/ (2 * a);
        double t2 = (-b + sqrt(discriminant))/ (2 * a);
        IntersectList iList = IntersectList();
        iList.appendIntersect(Intersect(t1, s));
        iList.appendIntersect(Intersect(t2, s));
        return iList;
    }
}
