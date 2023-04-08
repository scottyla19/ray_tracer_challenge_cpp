#ifndef RTC_MATERIAL
#define RTC_MATERIAL

#include <iostream>
#include <cmath>
#include "../primitives/Color.h"
#include "../primitives/Tuple.h"
#include "../primitives/constants.h"
#include "Light.h"

class Material{
private:
    Color m_color;
    double m_ambient;
    double m_diffuse;
    double m_specular;
    double m_shininess;

public:
    // constructors
    Material();
    Material(const Color& color, double ambient, double diffuse, double specular, double shininess);

    // accessors
    Color getColor()const{return m_color;}
    double getAmbient()const{return m_ambient;}
    double getDiffuse()const{return m_diffuse;}
    double getSpecular()const{return m_specular;}
    double getShininess()const{return m_shininess;}
    void setColor(const Color& c){m_color = c;}
    void setAmbient(double a){m_ambient = a;}
    void setDiffuse(double d){m_diffuse = d;}
    void setSpecular(double s){m_specular = s;}
    void setShininess(double s){m_shininess = s;}

    // operator overloads
    friend std::ostream& operator<< (std::ostream& out, const Material& mat);

    // member functions
    Color lighting(const Light& light, const Point& position, const Vector& eyev, const Vector& normalv );
    ~Material() = default;
};

bool operator==(const Material& t1, const Material& t2);






#endif
