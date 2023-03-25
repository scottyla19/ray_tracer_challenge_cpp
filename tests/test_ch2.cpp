#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <cmath>

#include "../primitives/Color.h"
#include "../primitives/constants.h"
#include "../scene/Canvas.h"


TEST_CASE("Colors are (red, green, blue) tuples") {
    Color c {Color(-0.5, 0.4, 1.7)};
    CHECK(typeid(c) == typeid(Color));
    CHECK(floatEqual(c.red(),-0.5));
    CHECK(floatEqual(c.green(), 0.4));
    CHECK(floatEqual(c.blue() , 1.7));
}

TEST_CASE("Adding colors"){
    Color c1 = Color(0.9, 0.6, 0.75);
    Color c2 = Color(0.7, 0.1, 0.25);
    CHECK(c1 + c2 == Color(1.6, 0.7, 1.0));
}

TEST_CASE("Subtracting colors"){
    Color c1 = Color(0.9, 0.6, 0.75);
    Color c2 = Color(0.7, 0.1, 0.25);
    CHECK(c1 - c2 == Color(0.2, 0.5, 0.5));
}
TEST_CASE("Multiplying colors by scalar"){
    Color c1 = Color(0.2, 0.3, 0.4);
    c1 *2.0;
    CHECK(c1 == Color(0.4, 0.6, 0.8));
}
TEST_CASE("Multiplying colors"){
    Color c1 = Color(1.0, 0.2, 0.4);
    Color c2 = Color(0.9, 1.0, 0.1);
    CHECK(c1*c2 == Color(0.9, 0.2, 0.04));
}
TEST_CASE("creating a canvas"){
    Canvas c = Canvas(10,20);
    CHECK(c.width() == 10);
    CHECK(c.height() == 20);
    bool isEqual = true;
    for(int i=0;i<c.width()*c.height();i++)
    if(c.pixels()[i]!=Color(0,0,0)){
        isEqual = false;
        break;
    }
    CHECK(isEqual);
}

TEST_CASE("Writing to a canvas"){
    Canvas c = Canvas(10,20);
    Color red = Color(1,0,0);
    c.write_pixel(2,3,red);
    CHECK(c.pixel_at(2,3) == red);
}
// TEST_CASE("constructing the PPM header"){
//     Canvas c = Canvas(5,3);
//     std::string ppm = c.canvas_to_ppm();
//     std::string ppm_str = std::string{ppm};
//     std::string line;
//     std::string header;
//     std::istringstream  lines(ppm_str);
//     int counter = 0;
//     while (std::getline(lines, line) &&  counter < 4 ) {
//         counter += 1;
//         header += line + "\n";
//     }
//     std::cout << ppm;
//     CHECK(ppm.compare("\nP3\n5 3\n255\n") == 0);
// }
TEST_CASE("Constructing ppm pixel data"){
    Canvas c = Canvas(5,3);
    c.write_pixel(0,0,Color(1.5,0,0));
    c.write_pixel(1,2,Color(0,0.5,0));
    c.write_pixel(2,4,Color(-0.5,0,1));
    std::string ppm = c.canvas_to_ppm();
    std::string expected = "\nP3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    CHECK(ppm.compare(expected) == 0);
}
//TEST_CASE("Splitting long lines in PPM"){
//    Canvas c = Canvas(10,2, Color(1, 0.8, 0.6));
//    std::string ppm = c.canvas_to_ppm();
//    std::string expected = "\nP3\n10 2\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n";
//    std::cout << ppm;
//    std::cout << expected;
//
//    CHECK(ppm.compare(expected) == 0);
//}

TEST_CASE("PPM ends with newline"){
    Canvas c = Canvas(5,3);
    std::string ppm = c.canvas_to_ppm();
    CHECK(ppm.back() == '\n');
}
