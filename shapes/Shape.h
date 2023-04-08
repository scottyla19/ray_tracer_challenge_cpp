#ifndef RTC_SHAPE
#define RTC_SHAPE

#include "../primitives/Tuple.h"
#include "../matrices/Matrix.h"
#include "../materials/Material.h"
//#include "../rays/Ray.h"
//#include "../rays/Intersect.h"
//#include "../primitives/constants.h"

class Shape{
private:


protected:
    static inline int s_id{1};
    int m_id{};
    Point m_origin;
    Matrix m_transform;
    Material m_material;

public:
    Shape();

    // accessors
    Point getOrigin()const{return m_origin;;}
    int getID()const {return m_id;}
    Matrix getTransform()const{return m_transform;}
    void setTransform(Matrix t){m_transform = t;}
    Material getMaterial()const{return m_material;}
    void setMaterial(const Material& material){m_material = material;}

    friend std::ostream& operator<< (std::ostream& out, const Shape& shape);


    // member functions
//    Intersect intersects(Ray r);
    Vector normal_at(const Point& p)const;



    ~Shape() = default;
};

bool operator==(const Shape& t1, const Shape& t2);

class Sphere: public Shape{
private:
//    int m_id;
//    Point m_origin;
    double m_radius;
//    Matrix m_transform;

public:
    Sphere();
    Sphere(Point origin , double radius );

    // accessors
    Point getOrigin(){return m_origin;}
    double getRadius() {return m_radius;}

    // member functions


    ~Sphere() = default;

};

#endif

