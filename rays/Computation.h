#ifndef RTC_COMPUTATION
#define RTC_COMPUTATION

#include "../shapes/Shape.h"
#include "Intersect.h"
#include "Ray.h"


class Computation{
private:
    double m_t;
    Shape m_object;
    Point m_point;
    Vector m_eyev;
    Vector m_normalv;
    bool m_isInside;

public:
    Computation(Intersect i, Ray r);

    const double getT()const{return m_t;}
    const Shape& getObject() const {return m_object;}
    const Point& getPoint() const {return m_point;}
    const Vector& getEyev() const {return m_eyev;}
    const Vector& getNormalv() const {return m_normalv;}


    bool isInside(){return m_isInside;}

    ~Computation() = default;
};




#endif // RTC_COMPUTATION
