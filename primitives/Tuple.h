#ifndef RTC_TUPLE
#define RTC_TUPLE
#include <iostream>

class Tuple
{
private:
    double m_x;
    double m_y;
    double m_z;
    double m_w;
public:
    // constructors
    Tuple(double x, double y, double z, double w);

    // accessors
    double x()const {return m_x;}
    double y()const{return m_y;}
    double z()const{return m_z;}
    double w()const{return m_w;}
    void setX(double x) {m_x = x;}
    void setY(double y) {m_y = y;}
    void setZ(double z) {m_z = z;}
    void setW(double w) {m_w = w;}

    // operator overloading
    Tuple operator- () const;
    Tuple operator*(double s);
    Tuple operator/(double s);

    friend std::ostream& operator<< (std::ostream& out, const Tuple& tuple);

    // member functions
    double magnitude();
    Tuple normalize();
    void set_index(int i, double value);

    ~Tuple() = default;
};
Tuple operator+(const Tuple& t1, const Tuple& t2);
Tuple operator-(const Tuple& t1, const Tuple& t2);
bool operator==(const Tuple& t1, const Tuple& t2);



class Point: public Tuple
{
private:
    /* data */
public:
    Point(double x, double y, double z);
    Point(const Tuple& t );
    Point();
    ~Point() = default;
};


class Vector: public Tuple
{
private:
    /* data */
public:
    Vector(double x, double y, double z);
    Vector(const Tuple& t );
    Vector() ;

    Vector& reflect(const Vector& normal)const;


    ~Vector() = default;
};
double dot(const Vector& v1, const Vector& v2);
Tuple cross(const Vector& v1, const Vector& v2);


#endif
