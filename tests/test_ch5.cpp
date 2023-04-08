#define _USE_MATH_DEFINES

#include "doctest.h"
#include <iostream>
#include <typeinfo>
#include <cmath>

#include "../rays/Ray.h"
#include "../shapes/Shape.h"
#include "../rays/Intersect.h"
#include "../matrices/Transform.h"



TEST_CASE("creating and quer)ing a ray"){
    Point origin = Point(1,2,3);
    Vector direction = Vector(4,5,6);
    Ray r = Ray(origin, direction);
    CHECK(r.getOrigin() == origin);
    CHECK(r.getDirection() == direction);
}

TEST_CASE("Computing point from a distance"){
    Ray r = Ray(Point(2,3,4), Vector(1,0,0));
    CHECK(r.position(0) == Point(2,3,4));
    CHECK(r.position(-1) == Point(1,3,4));
    CHECK(r.position(2.5) == Point(4.5,3,4));
}

TEST_CASE("ray intersects sphere twice"){
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Sphere s = Sphere();
    IntersectList xs = r.intersects(s);
    CHECK(xs.getCount() == 2);
    CHECK(xs[0].getT() == 4.0);
    CHECK(xs[1].getT() == 6.0);
}


TEST_CASE("ray intersects sphere tangent"){
    Ray r = Ray(Point(0,1,-5), Vector(0,0,1));
    Sphere s = Sphere();
    IntersectList xs = r.intersects(s);
    CHECK(xs.getCount() == 2);
    CHECK(xs[0].getT() == 5.0);
    CHECK(xs[1].getT() == 5.0);
}

TEST_CASE("ray intersects sphere misses"){
    Ray r = Ray(Point(0,2,-5), Vector(0,0,1));
    Sphere s = Sphere();
    IntersectList xs = r.intersects(s);
    CHECK(xs.getCount() == 0);
}

TEST_CASE("ray intersects sphere inside"){
    Ray r = Ray(Point(0,0,0), Vector(0,0,1));
    Sphere s = Sphere();
    IntersectList xs = r.intersects(s);
    CHECK(xs.getCount() == 2);
    CHECK(xs[0].getT() == -1.0);
    CHECK(xs[1].getT() == 1.0);
}

TEST_CASE("ray intersects sphere behind"){
    Ray r = Ray(Point(0,0,5), Vector(0,0,1));
    Sphere s = Sphere();
   IntersectList xs = r.intersects(s);
    CHECK(xs.getCount() == 2);
    CHECK(xs[0].getT() == -6.0);
    CHECK(xs[1].getT() == -4.0);
}

TEST_CASE("intersect encaps t and object")
{
    Sphere s = Sphere();
    Intersect i = Intersect(3.5, s);
    CHECK(i.getT() == 3.5);
    CHECK(i.getObject() == s);
}

TEST_CASE("aggregating intersections")
{
    Sphere s = Sphere();
    Intersect i = Intersect(1, s);
    Intersect i2 = Intersect(2, s);
    IntersectList xs = IntersectList();
    xs.appendIntersect(i);
    xs.appendIntersect(i2);
    CHECK(xs.getCount() == 2);
    CHECK(xs[0].getT() == 1.0);
    CHECK(xs[1].getT() == 2.0);
}

TEST_CASE("intersect sets object on the intersection"){
    Ray r = Ray(Point(0,0,5), Vector(0,0,1));
    Sphere s = Sphere();
    IntersectList xs = r.intersects(s);
    CHECK(xs.getCount() == 2);
    CHECK(xs[0].getObject() == s);
    CHECK(xs[1].getObject() == s);
}

TEST_CASE("Hit when all intersecions positive")
{
    Sphere s = Sphere();
    Intersect i1 = Intersect(1, s);
    Intersect i2 = Intersect(2, s);
    IntersectList xs = IntersectList();
    xs.appendIntersect(i1);
    xs.appendIntersect(i2);
    Intersect* i = xs.hit();
    CHECK(*i == i1);
}

TEST_CASE("Hit when some intersections negative")
{
    Sphere s = Sphere();
    Intersect i1 = Intersect(-1, s);
    Intersect i2 = Intersect(1, s);
    IntersectList xs = IntersectList();
    xs.appendIntersect(i2);
    xs.appendIntersect(i1);
    Intersect* i = xs.hit();
    CHECK(*i == i2);
}

TEST_CASE("Hit when all intersections negative")
{
    Sphere s = Sphere();
    Intersect i1 = Intersect(-1, s);
    Intersect i2 = Intersect(-2, s);
    IntersectList xs = IntersectList();
    xs.appendIntersect(i2);
    xs.appendIntersect(i1);
    Intersect* i = xs.hit();
    CHECK(*i == nullptr);
}

TEST_CASE("Hit is always lowest non-negative")
{
    Sphere s = Sphere();
    Intersect i1 = Intersect(5, s);
    Intersect i2 = Intersect(7, s);
    Intersect i3 = Intersect(-3, s);
    Intersect i4 = Intersect(2, s);
    IntersectList xs = IntersectList();
    xs.appendIntersect(i1);
    xs.appendIntersect(i2);
    xs.appendIntersect(i3);
    xs.appendIntersect(i4);
    Intersect* i = xs.hit();
    CHECK(*i == i4);
}

TEST_CASE("translating a ray"){
    Ray r = Ray(Point(1,2,3), Vector(0,1,0));
    Translation t = Translation(3,4,5);
    Ray r2 = r.transform(t);
    CHECK(r2.getOrigin() == Point(4,6,8));
    CHECK(r2.getDirection() == Vector(0,1,0));
}

TEST_CASE("scaling a ray"){
    Ray r = Ray(Point(1,2,3), Vector(0,1,0));
    Scaling t = Scaling(2,3,4);
    Ray r2 = r.transform(t);
    CHECK(r2.getOrigin() == Point(2,6,12));
    CHECK(r2.getDirection() == Vector(0,3,0));
}

TEST_CASE("sphere default transformation"){
    Sphere s = Sphere();
    CHECK(s.getTransform() == Matrix(4,4));
}

TEST_CASE("Sphere's change transformation"){
    Sphere s = Sphere();
    Translation t = Translation(2,3,4);
    s.setTransform(t);
    CHECK(s.getTransform() == t);
}

TEST_CASE("intersecting a scaled sphere"){
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Sphere s = Sphere();
    s.setTransform(Scaling(2,2,2));
    IntersectList xs = r.intersects(s);
    CHECK(xs.getCount() == 2);
    CHECK(xs[0].getT() == 3.0);
    CHECK(xs[1].getT() == 7.0);
}

TEST_CASE("intersecting a translated sphere"){
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Sphere s = Sphere();
    s.setTransform(Translation(5,0,0));
    IntersectList xs = r.intersects(s);
    CHECK(xs.getCount() == 0);
}


