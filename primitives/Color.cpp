#include "Color.h"
#include "constants.h"


Color::Color(double r, double g, double b){
    m_red = r;
    m_green = g;
    m_blue = b;
}
Color::Color() {
    m_red = 0.0;
    m_green = 0.0;
    m_blue = 0.0;
}

Color operator+(const Color& t1, const Color& t2){
    return Color(t1.red() + t2.red(), t1.green() + t2.green(), t1.blue() + t2.blue());
}
Color operator-(const Color& t1, const Color& t2){
    return Color(t1.red() - t2.red(), t1.green() - t2.green(), t1.blue() - t2.blue());

}

Color Color::operator*(double s){
    double r = m_red * s;
    double g = m_green * s;
    double b = m_blue * s;
    return Color(r, g, b);
}

Color operator*(const Color& t1, const Color& t2){
    return Color(t1.red()*t2.red(), t1.green()*t2.green(), t1.blue()*t2.blue());
}

bool operator==(const Color& t1, const Color& t2){
    return floatEqual(t1.red() , t2.red()) &&
    floatEqual(t1.green() , t2.green())&&
    floatEqual(t1.blue() , t2.blue());
}

bool operator!=(const Color& t1, const Color& t2){
    return !floatEqual(t1.red() , t2.red()) ||
    !floatEqual(t1.green() , t2.green()) ||
    !floatEqual(t1.blue() , t2.blue());
}

std::ostream& operator<< (std::ostream& out, const Color& color){
    out << "Color(r:" << color.red() << ", g:" << color.green() << ", b: " << color.blue() <<')';
    return out; // return s
}

