#ifndef RTC_LIGHT
#define RTC_LIGHT

#include <iostream>
#include "../primitives/Color.h"
#include "../primitives/Tuple.h"

class Light{
private:
    Color m_intensity;
    Point m_position;

public:
    Light();
    Light(Point position, Color intensity);

    Color getIntensity()const{return m_intensity;}
    Point getPosition()const{return m_position;}


    friend bool operator==(const Light& l1, const Light& l2);
    friend std::ostream& operator<< (std::ostream& out, const Light& light);


    ~Light() = default;

};




#endif
