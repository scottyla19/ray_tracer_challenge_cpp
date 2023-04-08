#include "Intersect.h"
#include<algorithm>


Intersect::Intersect(Shape s): m_object{s}
{
}

Intersect::Intersect(double t, Shape s): m_object{s}, m_t{t}
{
}



bool Intersect::operator<(const Intersect& b){
    return m_t < b.getT();
}

std::ostream& operator<< (std::ostream& out, const Intersect& i){
    out << "Intersect at " << i.getT() << " with shapeID " << i.getObject().getID();
    return out;
}

bool Intersect::operator==( const Intersect& b){
    return (m_object == b.getObject() && m_t == b.getT());
}

bool Intersect::operator==(std::nullptr_t ){
    return this == nullptr;
}


IntersectList::IntersectList()
{
}

void IntersectList::appendIntersect(Intersect i){
    m_intersects.push_back(i);
    std::sort(m_intersects.begin(), m_intersects.end());
}

const std::vector<Intersect>& IntersectList::getIntersects(){
    return m_intersects;
}

const Intersect IntersectList::operator[](int i){
    return m_intersects[i];
}

Intersect* IntersectList::hit(){
    std::sort(m_intersects.begin(), m_intersects.end());
    for (int i = 0; i < m_intersects.size();i++){
        if (m_intersects[i].getT() >= 0.0){
            return &m_intersects[i];
        }
    }
    Intersect* npt {nullptr};
    return npt;
}

