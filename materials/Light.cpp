#include "Light.h"

Light::Light(): m_position{Point(0,0,0)}, m_intensity{Color(1,1,1)}
{
}
Light::Light(Point position , Color intensity):  m_position{position}, m_intensity{intensity}
{
}

bool operator==(const Light& l1, const Light& l2){
    return (l1.getIntensity() == l2.getIntensity() && l1.getPosition() == l2.getPosition());
}

std::ostream& operator<< (std::ostream& out, const Light& light){
    out << "Intensity: " << light.getIntensity() << " Position: " << light.getPosition() << std::endl;
    return out;
}


