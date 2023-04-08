#ifndef RTC_INTERSECT
#define RTC_INTERSECT

#include <vector>
#include "../shapes/Shape.h"

class Intersect
{
private:
    Shape m_object;
    double m_t;

public:
    Intersect(Shape s);
    Intersect(double t, Shape s);

    // accessor functions
    const Shape& getObject()const{return m_object;}
    double getT()const{return m_t;}


    // operator overloads
    const double operator[](int i);
    bool operator<(const Intersect& b);
    bool operator==(const Intersect& b);
    bool operator==(std::nullptr_t);
    friend std::ostream& operator<< (std::ostream& out, const Intersect& i);


    // member functions

    ~Intersect() = default;
};
//bool operator<(const Intersect& l, const Intersect& r);
//bool operator==(const Intersect& l, const Intersect& r);

class IntersectList
{
private:
    std::vector<Intersect> m_intersects;
public:
    IntersectList();

    // accessors
    const int getCount(){return m_intersects.size();}
    const std::vector<Intersect>& getIntersects();
    void appendIntersect(Intersect i);


    // operator overload
    const Intersect operator[](int i);

    // member functions
    Intersect* hit();

    ~IntersectList() = default;
};


#endif
