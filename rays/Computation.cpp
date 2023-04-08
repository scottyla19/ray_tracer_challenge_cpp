#include "Computation.h"

Computation::Computation(Intersect i, Ray r): m_t{i.getT()}, m_object{i.getObject()}
{
    m_point = r.position(m_t);
    m_eyev = -r.getDirection();
    m_normalv = m_object.normal_at(m_point);
    if (dot(m_normalv, m_eyev) < 0){
        m_isInside = true;
        m_normalv = -m_normalv;
    }else{
        m_isInside = false;
    }

}
