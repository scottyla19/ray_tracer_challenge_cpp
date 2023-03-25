#define _USE_MATH_DEFINES

#include "doctest.h"
#include <iostream>
#include <typeinfo>
#include <cmath>

#include "../matrices/Transform.h"

TEST_CASE("multiplying by a translation matrix"){
    Translation t = Translation(5.0, -3.0, 2.0);
    Point p = Point(-3.0, 4.0, 5.0);
    CHECK(t * p == Point(2.0, 1.0, 7.0));
}

TEST_CASE("multiplying by inverse of a translation matrix"){
    Translation t = Translation(5.0, -3.0, 2.0);
    Matrix inv = t.inverse();
    Point p = Point(-3.0, 4.0, 5.0);
    CHECK(inv * p == Point(-8.0, 7.0, 3.0));
}

TEST_CASE("multiplying by inverse of a translation matrix"){
    Matrix t = Translation(5.0, -3.0, 2.0);
    Vector v = Vector(-3.0, 4.0, 5.0);
    CHECK(t * v == v);
}

TEST_CASE("scaling applied to point"){
    Scaling t = Scaling(2.0, 3.0, 4.0);
    Point p = Point(-4.0, 6.0, 8.0);
    CHECK(t * p == Point(-8.0, 18.0, 32.0));
}

TEST_CASE("scaling applied to vector"){
    Scaling t = Scaling(2.0, 3.0, 4.0);
    Vector v = Vector(-4.0, 6.0, 8.0);
    CHECK(t * v == Vector(-8.0, 18.0, 32.0));
}

TEST_CASE("multiplying by inverse of scaling"){
    Scaling t = Scaling(2.0, 3.0, 4.0);
    Matrix inv = t.inverse();
    Point p = Point(-4.0, 6.0, 8.0);
    CHECK(inv * p == Point(-2.0, 2.0, 2.0));
}

TEST_CASE("reflection with scaling"){
    Scaling t = Scaling(-1.0, 1.0, 1.0);
    Vector v = Vector(2.0, 3.0, 4.0);
    CHECK(t * v == Vector(-2.0, 3.0, 4.0));
}

TEST_CASE("rotating around x axis"){
    Point p = Point(0,1,0);
    Rotation half_quarter = Rotation('x', M_PI_4);
    Rotation full_quarter = Rotation('x', M_PI_2);
    CHECK(half_quarter * p == Point(0.0, sqrt(2)/2, sqrt(2)/2));
    CHECK(full_quarter * p == Point(0.0, 0.0, 1.0));
}

TEST_CASE("rotating around x axis inverse"){
    Point p = Point(0,1,0);
    Rotation half_quarter = Rotation('x', M_PI_4);
    Matrix inv = half_quarter.inverse();
    CHECK(inv * p == Point(0.0, sqrt(2)/2, -sqrt(2)/2));
}

TEST_CASE("rotating around y axis"){
    Point p = Point(0,0,1);
    Rotation half_quarter = Rotation('y', M_PI_4);
    Rotation full_quarter = Rotation('y', M_PI_2);
    CHECK(half_quarter * p == Point(sqrt(2)/2, 0.0, sqrt(2)/2));
    CHECK(full_quarter * p == Point(1.0, 0.0, 0.0));
}

TEST_CASE("rotating around z axis"){
    Point p = Point(0,1,0);
    Rotation half_quarter = Rotation('z', M_PI_4);
    Rotation full_quarter = Rotation('z', M_PI_2);
    CHECK(half_quarter * p == Point(-sqrt(2)/2, sqrt(2)/2, 0.0));
    CHECK(full_quarter * p == Point(-1.0, 0.0, 0.0));
}

TEST_CASE("shearing moves x in respect to y"){
    Shearing t = Shearing(1,0,0,0,0,0);
    Point p = Point(2,3,4);
    CHECK(t * p == Point (5,3,4));
}

TEST_CASE("shearing moves x in respect to z"){
    Shearing t = Shearing(0,1,0,0,0,0);
    Point p = Point(2,3,4);
    CHECK(t * p == Point (6,3,4));
}

TEST_CASE("shearing moves y in respect to x"){
    Shearing t = Shearing(0,0,1,0,0,0);
    Point p = Point(2,3,4);
    CHECK(t * p == Point (2,5,4));
}

TEST_CASE("shearing moves y in respect to z"){
    Shearing t = Shearing(0,0,0,1,0,0);
    Point p = Point(2,3,4);
    CHECK(t * p == Point (2,7,4));
}

TEST_CASE("shearing moves z in respect to x"){
    Shearing t = Shearing(0,0,0,0,1,0);
    Point p = Point(2,3,4);
    CHECK(t * p == Point (2,3,6));
}

TEST_CASE("shearing moves z in respect to y"){
    Shearing t = Shearing(0,0,0,0,0,1);
    Point p = Point(2,3,4);
    CHECK(t * p == Point (2,3,7));
}

TEST_CASE("individual transformations are applied in reverse"){
    Point p = Point(1,0,1);
    Rotation a = Rotation('x', M_PI_2);
    Scaling b = Scaling(5,5,5);
    Translation c = Translation(10, 5,7);
    Point p2 = a * p;
    CHECK(p2 == Point (1, -1, 0));
    Point p3 = b * p2;
    CHECK(p3 == Point (5, -5, 0));
    Point p4 = c * p3;
    CHECK(p4 == Point (15, 0, 7));
}

TEST_CASE("chained transformations are applied in reverse"){
    Point p = Point(1,0,1);
    Rotation a = Rotation('x', M_PI_2);
    Scaling b = Scaling(5,5,5);
    Translation c = Translation(10, 5,7);
    Matrix t = c * b * a;
    CHECK(t * p == Point(15, 0, 7));
}


