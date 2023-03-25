#include "doctest.h"
#include <iostream>
#include <typeinfo>
#include <cmath>

#include "../primitives/Tuple.h"
#include "../primitives/constants.h"

TEST_CASE("test with w=1 is a point") {
    Tuple a {Tuple(4.3, -4.2, 3.1,1.0)};
    CHECK(typeid(a) == typeid(Tuple));
    CHECK(floatEqual(a.x(),4.3));
    CHECK(floatEqual(a.y(), -4.2));
    CHECK(floatEqual(a.z() , 3.1));
    CHECK(floatEqual(a.w()  , 1.0));
}

TEST_CASE("test point creates tuple w=1") {
    Point a {Point(4.0, -4.0, 3.0)};
    CHECK(typeid(a) == typeid(Point));
    CHECK(dynamic_cast<Tuple*>(&a));
    CHECK(floatEqual(a.x(),4.0));
    CHECK(floatEqual(a.y(), -4.0));
    CHECK(floatEqual(a.z() , 3.0));
    CHECK(floatEqual(a.w()  , 1.0));
}

TEST_CASE("test vector creates tuple w=0") {
    Vector a {Vector(4.0, -4.0, 3.0)};
    CHECK(typeid(a) == typeid(Vector));
    CHECK(dynamic_cast<Tuple*>(&a));
    CHECK(floatEqual(a.x(),4.0));
    CHECK(floatEqual(a.y(), -4.0));
    CHECK(floatEqual(a.z() , 3.0));
    CHECK(floatEqual(a.w()  , 0.0));
}

TEST_CASE("adding two tuples") {
    Tuple a {Tuple(3, -2, 5, 1)};
    Tuple b {Tuple(-2, 3, 1, 0)};
    CHECK(a + b == Tuple(1, 1, 6, 1));

}

TEST_CASE("subracting two points") {
    Tuple a {Point(3, 2,1)};
    Tuple b {Point(5,6,7)};
    CHECK(a - b == Vector(-2,-4,-6));
}
TEST_CASE("subracting vector from point") {
    Tuple a {Point(3, 2,1)};
    Tuple b {Vector(5,6,7)};
    CHECK(a - b == Point(-2,-4,-6));
}

TEST_CASE("negating a tuple") {
    Tuple a {Tuple(1, -2, 3, -4)};
    CHECK(-a == Tuple(-1, 2, -3, 4));

}
TEST_CASE("multiplying tuple and scalar") {
    Tuple a {Tuple(1, -2, 3, -4)};
    a *3.5;
    CHECK(a == Tuple(3.5, -7, 10.5, -14));
}

TEST_CASE("multiplying tuple by fraction") {
    Tuple a {Tuple(1, -2, 3, -4)};
    a *0.5;
    CHECK(a == Tuple(0.5, -1, 1.5, -2));
}
TEST_CASE("dividing tuple by fraction") {
    Tuple a {Tuple(1, -2, 3, -4)};
    a / 2;
    CHECK(a == Tuple(0.5, -1, 1.5, -2));
}

TEST_CASE("magnitude of vector") {
    Vector a {Vector(1,0,0)};
    CHECK(a.magnitude() == 1);
    Vector b {Vector(0,1,0)};
    CHECK(b.magnitude() == 1);
    Vector c {Vector(0,0,1)};
    CHECK(c.magnitude() == 1);
    Vector d {Vector(1,2,3)};
    CHECK(floatEqual(d.magnitude(), std::sqrt(14)));
    Vector e {Vector(-1,-2,-3)};
    CHECK(floatEqual(e.magnitude(), std::sqrt(14)));
}

TEST_CASE("normalizing vectors"){
    Vector a {Vector(4,0,0)};
    CHECK(a.normalize() == Vector(1,0,0));
    Vector b {Vector(1,2,3)};
    CHECK(b.normalize() == Vector(1/std::sqrt(14),2/std::sqrt(14),3/std::sqrt(14)));
    Vector norm = b.normalize();
    CHECK(floatEqual(norm.magnitude() , 1));
}

TEST_CASE("dot product"){
    Vector a {Vector(1,2,3)};
    Vector b {Vector(2,3,4)};
    CHECK(floatEqual(dot(a,b), 20));
}

TEST_CASE("dot product"){
    Vector a {Vector(1,2,3)};
    Vector b {Vector(2,3,4)};
    CHECK(cross(a,b) == Vector(-1,2,-1));
    CHECK(cross(b,a) == Vector(1,-2,1));

}
