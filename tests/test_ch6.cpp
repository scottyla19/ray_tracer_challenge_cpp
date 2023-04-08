#define _USE_MATH_DEFINES

#include "doctest.h"
#include <iostream>
#include <cmath>

#include "../shapes/Shape.h"
#include "../primitives/Tuple.h"
#include "../matrices/Transform.h"
#include "../primitives/Color.h"
#include "../materials/Light.h"
#include "../materials/Material.h"

TEST_CASE("normal on a sphere at point on x axis"){
    Sphere s = Sphere();
    Vector n = s.normal_at(Point(1,0,0));
    CHECK(n == Vector(1,0,0));
}

TEST_CASE("normal on a sphere at point on y axis"){
    Sphere s = Sphere();
    Vector n = s.normal_at(Point(0,1,0));
    CHECK(n == Vector(0,1,0));
}

TEST_CASE("normal on a sphere at point on z axis"){
    Sphere s = Sphere();
    Vector n = s.normal_at(Point(0,0,1));
    CHECK(n == Vector(0,0,1));
}

TEST_CASE("normal on a sphere at point on non-axial point"){
    Sphere s = Sphere();
    Vector n = s.normal_at(Point(sqrt(3)/3,sqrt(3)/3,sqrt(3)/3));
    CHECK(n == Vector(sqrt(3)/3,sqrt(3)/3,sqrt(3)/3));
}

TEST_CASE("normal on a sphere is normalized"){
    Sphere s = Sphere();
    Vector n = s.normal_at(Point(sqrt(3)/3,sqrt(3)/3,sqrt(3)/3));
    CHECK(n == n.normalize());
}

TEST_CASE("normal on a translated sphere"){
    Sphere s = Sphere();
    s.setTransform(Translation(0,1,0));
    Vector n = s.normal_at(Point(0, 1.70711, -0.70711));
    CHECK(n == Vector(0, 0.70711, -0.70711));
}

TEST_CASE("normal on a transformed sphere"){
    Sphere s = Sphere();
    Matrix m = Scaling(1, 0.5, 1) * Rotation('z', M_PI/5);
    s.setTransform(m);

    Vector n = s.normal_at(Point(0,sqrt(2)/2,-sqrt(2)/2));
    CHECK(n == Vector(0, 0.970143, -0.242536));
}

TEST_CASE("Reflecting vector at 45"){
    Vector v = Vector(1, -1,0);
    Vector n = Vector(0,1,0);
    Vector r = v.reflect( n);
    CHECK(r == Vector(1,1,0));
}

TEST_CASE("Reflecting vector off slanted surface"){
    Vector v = Vector(0, -1,0);
    Vector n = Vector(sqrt(2)/2,sqrt(2)/2,0);
    Vector r = v.reflect( n);
    CHECK(r == Vector(1,0,0));
}

TEST_CASE("point light has position and intensity"){
    Color intensity = Color(1,1,1);
    Point position = Point(0,0,0);
    Light light = Light(position, intensity);
    CHECK(light.getPosition() == position);
    CHECK(light.getIntensity() == intensity);
}

TEST_CASE("default material"){
    Material m = Material();
    CHECK(m.getColor() == Color(1,1,1));
    CHECK(m.getAmbient() == 0.1);
    CHECK(m.getDiffuse() == 0.9);
    CHECK(m.getShininess() == 200.0);
    CHECK(m.getSpecular() == 0.9);
}

TEST_CASE("sphere has default material"){
    Sphere s = Sphere();
    CHECK(s.getMaterial() == Material());
}

TEST_CASE("sphere assign material"){
    Sphere s = Sphere();
    Material m = Material();
    m.setAmbient(1.0);
    s.setMaterial(m);
    CHECK(s.getMaterial() == m);
}
TEST_CASE("lighting with eye between light and surface"){
    Vector eyev = Vector(0,0,-1);
    Vector normalv = Vector(0,0,-1);
    Light light = Light(Point(0,0,-10), Color(1,1,1));
    Point position = Point(0,0,0);
    Material m = Material();
    Color result = m.lighting(light, position, eyev, normalv);
    CHECK(result == Color(1.9,1.9,1.9));
}

TEST_CASE("lighting with eye between light and surface eye offset 45"){
    Vector eyev = Vector(0,sqrt(2)/2,sqrt(2)/2);
    Vector normalv = Vector(0,0,-1);
    Light light = Light(Point(0,0,-10), Color(1,1,1));
    Point position = Point(0,0,0);
    Material m = Material();
    Color result = m.lighting(light, position, eyev, normalv);
    CHECK(result == Color(1.0,1.0,1.0));
}

TEST_CASE("lighting with eye opposite surface eye offset 45"){
    Vector eyev = Vector(0,0, -1);
    Vector normalv = Vector(0,0,-1);
    Light light = Light(Point(0,10,-10), Color(1,1,1));
    Point position = Point(0,0,0);
    Material m = Material();
    Color result = m.lighting(light, position, eyev, normalv);
    CHECK(result == Color(0.7364, 0.7364, 0.7364));
}

TEST_CASE("lighting with eye in path of reflection vector"){
    Vector eyev = Vector(0,-sqrt(2)/2,-sqrt(2)/2);
    Vector normalv = Vector(0,0,-1);
    Light light = Light(Point(0,10,-10), Color(1,1,1));
    Point position = Point(0,0,0);
    Material m = Material();
    Color result = m.lighting(light, position, eyev, normalv);
    CHECK(result == Color(1.6364, 1.6364, 1.6364));
}
TEST_CASE("lighting with light behind surface"){
    Vector eyev = Vector(0,0, -1);
    Vector normalv = Vector(0,0,-1);
    Light light = Light(Point(0,0,10), Color(1,1,1));
    Point position = Point(0,0,0);
    Material m = Material();
    Color result = m.lighting(light, position, eyev, normalv);
    CHECK(result == Color(0.1, 0.1, 0.1));
}




