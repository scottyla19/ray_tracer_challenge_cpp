#include "Material.h"

Material::Material():
    m_color{Color(1,1,1)},
    m_ambient{0.1},
    m_diffuse{0.9},
    m_specular{0.9},
    m_shininess{200.0}
{
}

Material::Material(const Color& color, double ambient, double diffuse, double specular, double shininess):
    m_color{color},
    m_ambient{ambient},
    m_diffuse{diffuse},
    m_specular{specular},
    m_shininess{shininess}
{
}

Color Material::lighting(const Light& light, const Point& position, const Vector& eyev, const Vector& normalv )
{
    Color effective_color = m_color * light.getIntensity();
    Vector lightv = (light.getPosition() - position).normalize();
    Color ambient_contr = effective_color * m_ambient;
    double lightDotNormal = dot(lightv, normalv);
    Color diffuse = Color(0,0,0);
    Color specular = Color(0,0,0);
    if (lightDotNormal < 0.0){
        diffuse = Color(0,0,0);
        specular = Color(0,0,0);
    }
    else{
        diffuse = effective_color * m_diffuse * lightDotNormal;

        Vector reflectv = -lightv.reflect(normalv);
        double reflect_dot_eye = dot(reflectv, eyev);

        if (reflect_dot_eye <= 0.0){
            specular = Color(0,0,0);
        }
        else{
            double factor = pow(reflect_dot_eye, m_shininess);
            specular = light.getIntensity() * m_specular * factor;
        }
    }
    return ambient_contr + diffuse + specular;
}

bool operator==(const Material& m1, const Material& m2){
    return m1.getColor() == m2.getColor() &&
            floatEqual(m1.getAmbient() , m2.getAmbient() )&&
            floatEqual(m1.getDiffuse(), m2.getDiffuse()) &&
            floatEqual(m1.getSpecular(), m2.getSpecular()) &&
            floatEqual(m1.getShininess(), m2.getShininess());
}

std::ostream& operator<< (std::ostream& out, const Material& mat){
    out << "Color: " << mat.getColor() << " ambient: " << mat.getAmbient() <<
    " diffuse: " << mat.getDiffuse() << " specular: " << mat.getSpecular() <<
    " shininess: " << mat.getShininess() << std::endl;
    return out;
}

