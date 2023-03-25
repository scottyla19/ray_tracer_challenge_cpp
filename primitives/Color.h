#pragma once
#include <iostream>

class Color
{
private:
    double m_red;
    double m_green;
    double m_blue;
public:
    Color(double r, double g, double b);
    Color();

    double red()const {return m_red;}
    double green() const {return m_green;}
    double blue() const {return m_blue;}
    void set_red(double r) {m_red = r;}
    void set_green(double g) {m_green = g;}
    void set_blue(double b) {m_blue = b;}

    void operator*(double s);
    friend std::ostream& operator<< (std::ostream& out, const Color& color);
    ~Color() = default;
};
Color operator+(const Color& t1, const Color& t2);
Color operator-(const Color& t1, const Color& t2);
Color operator*(const Color& t1, const Color& t2);
bool operator==(const Color& t1, const Color& t2);
bool operator!=(const Color& t1, const Color& t2);




