#define _USE_MATH_DEFINES

#include "doctest.h"
#include <iostream>
#include <cmath>
#include <algorithm>

#include "../scene/World.h"
#include "../matrices/Transform.h"
#include "../shapes/Shape.h"
#include "../materials/Light.h"
#include "../rays/Ray.h"
#include "../rays/Intersect.h"
#include "../rays/Computation.h"
#include "../primitives/constants.h"



TEST_CASE("creating a world"){
    World w = World();
    CHECK(w.getLights().empty());
    CHECK(w.getObjects().empty());
}

TEST_CASE("default world"){
    Light light = Light(Point(-10,10,-10), Color(1,1,1));
    Sphere s1 = Sphere();
    Material mat = Material();
    mat.setColor(Color(0.8,1.0,0.6));
    mat.setDiffuse(0.7);
    mat.setSpecular(0.2);
    s1.setMaterial(mat);
    Sphere s2 = Sphere();
    s2.setTransform(Scaling(0.5,0.5,0.5));
    World w = World(true);
    std::vector<Light> l = w.getLights();
    CHECK(l[0] == light);
    CHECK(std::find(w.getObjects().begin(), w.getObjects().end(),s1) != w.getObjects().end());
    CHECK(std::find(w.getObjects().begin(), w.getObjects().end(),s2)!= w.getObjects().end());
}

TEST_CASE("intersect world with ray"){
    World w = World(true);
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    IntersectList xs = w.intersect_world(r);
    CHECK(xs.getCount() == 4);
    CHECK(floatEqual(xs[0].getT(), 4.0));
    CHECK(floatEqual(xs[1].getT(), 4.5));
    CHECK(floatEqual(xs[2].getT(), 5.5));
    CHECK(floatEqual(xs[3].getT(), 6.0));
}

TEST_CASE("precomputing intersection state"){
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Sphere shape = Sphere();
    Intersect i = Intersect(4,shape);
    Computation comps = Computation(i, r);
    CHECK(floatEqual(comps.getT(), i.getT()));
    CHECK(comps.getObject() == i.getObject());
    CHECK(comps.getPoint() == Point(0,0,-1));
    CHECK(comps.getEyev() == Vector(0,0,-1));
    CHECK(comps.getNormalv() == Vector(0,0,-1));
}

TEST_CASE("The hit when intersection is outside"){
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Sphere shape = Sphere();
    Intersect i = Intersect(4, shape);
    Computation comps = Computation(i, r);
    CHECK(!comps.isInside());
}

TEST_CASE("The hit when intersection is inside"){
    Ray r = Ray(Point(0,0,0), Vector(0,0,1));
    Sphere shape = Sphere();
    Intersect i = Intersect(1, shape);
    Computation comps = Computation(i, r);
    CHECK(comps.getPoint() == Point(0,0,1));
    CHECK(comps.getEyev() == Vector(0,0,-1));
    CHECK(comps.getNormalv() == Vector(0,0,-1));
    CHECK(comps.isInside());
}

TEST_CASE("shading an intersectoin")
{
    World w = World(true);
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Shape shape = w.getObjects()[0];
    Intersect i = Intersect(4, shape);
    Computation comps = Computation(i, r);
    Color c = w.shade_hit(comps);
    CHECK(c == Color(0.380661, 0.475826, 0.285496) );
}

TEST_CASE("shading an intersection from inside")
{
    World w = World(true);
    Light light = Light(Point(0, 0.25, 0), Color(1, 1, 1));
    w.replaceLightAt(light, 0);
    Ray r = Ray(Point(0,0,0), Vector(0,0,1));
    Shape shape = w.getObjects()[1];
    Intersect i = Intersect(0.5, shape);
    Computation comps = Computation(i, r);
    Color c = w.shade_hit(comps);
    CHECK(c == Color(0.90498, 0.90498, 0.90498) );
}

TEST_CASE("color when ray misses")
{
    World w = World(true);
    Ray r = Ray(Point(0,0,-5), Vector(0,1,0));
    Color c = w.color_at(r);
    CHECK(c == Color(0, 0, 0));
}

TEST_CASE("color when ray hits")
{
    World w = World(true);
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Color c = w.color_at(r);
    CHECK(c == Color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("color when behind a ray")
{
    World w = World(true);
    Shape outer = w.getObjects()[0];
    Material m = outer.getMaterial();
    m.setAmbient(1);
    outer.setMaterial(m);
    w.replaceObjectAt(outer, 0);
    Shape inner = w.getObjects()[1];
    inner.setMaterial(m);
    w.replaceObjectAt(inner, 1);
    Ray r = Ray(Point(0,0,0.75), Vector(0,0,-1));
    Color c = w.color_at(r);
    CHECK(c == inner.getMaterial().getColor());
}

TEST_CASE("view transform default")
{
    Point from = Point(0,0,0);
    Point to = Point(0,0,-1);
    Vector up = Vector(0,1,0);
    Matrix t = view_transform(from, to , up);
    CHECK(t == Matrix(4, 4));
}

TEST_CASE("view transform in positive z")
{
    Point from = Point(0,0,0);
    Point to = Point(0,0,1);
    Vector up = Vector(0,1,0);
    Matrix t = view_transform(from, to , up);
    CHECK(t == Scaling(-1, 1,-1));
}

TEST_CASE("view transform moves the world")
{
    Point from = Point(0,0,8);
    Point to = Point(0,0,0);
    Vector up = Vector(0,1,0);
    Matrix t = view_transform(from, to , up);
    CHECK(t == Translation(0,0,-8));
}

TEST_CASE("view transform arbitrary")
{
    Point from = Point(1,3,2);
    Point to = Point(4,-2,8);
    Vector up = Vector(1,1,0);
    Matrix t = view_transform(from, to , up);
    std::vector<double> data = {
        -0.50709 , 0.50709 ,  0.67612 , -2.36643 ,
        0.76772 , 0.60609 ,  0.12122 , -2.82843 ,
        -0.35857 , 0.59761 , -0.71714 ,  0.00000 ,
        0.00000 , 0.00000 ,  0.00000 ,  1.00000};
    CHECK(t == Matrix(4, 4, data));
}

TEST_CASE("constructing a camera")
{
    int hsize = 160;
    int vsize = 120;
    double field_of_view = M_PI_2;
    Camera c = Camera(hsize, vsize, field_of_view);
    CHECK(c.getHsize() == 160);
    CHECK(c.getVsize() == 120);
    CHECK(floatEqual(c.getField_of_view(), M_PI_2));
    CHECK(c.getTransform() == Matrix(4,4));
}

TEST_CASE("pixel size for horizontal canvas")
{
    Camera c = Camera(200, 125, M_PI_2);
    CHECK(floatEqual(c.getPixel_size(), 0.01));
}

TEST_CASE("pixel size for vertical canvas")
{
    Camera c = Camera(125, 200, M_PI_2);
    CHECK(floatEqual(c.getPixel_size(), 0.01));
}

TEST_CASE("constructing ray through center of canvas")
{
    Camera c = Camera(201, 101, M_PI_2);
    Ray r = c.ray_for_pixel(100, 50);
    CHECK(r.getOrigin() == Point(0,0,0));
    CHECK(r.getDirection() == Vector(0,0,-1));
}

TEST_CASE("constructing ray through corner of canvas")
{
    Camera c = Camera(201, 101, M_PI_2);
    Ray r = c.ray_for_pixel(0,0);
    CHECK(r.getOrigin() == Point(0,0,0));
    CHECK(r.getDirection() == Vector(0.66519, 0.33259, -0.66851));
}

TEST_CASE("constructing ray when camera is transformed")
{
    Camera c = Camera(201, 101, M_PI_2);
    c.setTransform(Rotation('y', M_PI_4) * Translation(0,-2,5));
    Ray r = c.ray_for_pixel(100, 50);
    CHECK(r.getOrigin() == Point(0,2,-5));
    CHECK(r.getDirection() == Vector(sqrt(2)/2, 0,-sqrt(2)/2));
}

TEST_CASE("render a world with camera")
{
    World w = World(true);
    Camera c = Camera(11, 11, M_PI_2);
    Point from = Point(0,0,-5);
    Point to = Point(0,0,0);
    Vector up = Vector(0,1,0);
    Matrix t = view_transform(from, to , up);
    c.setTransform(t);
    Canvas image = c.render(w);
    CHECK(image.pixel_at(5,5) == Color(0.38066, 0.47583, 0.2855));
}
