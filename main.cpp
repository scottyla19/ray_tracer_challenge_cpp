#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include "primitives/Tuple.h"
#include "primitives/constants.h"
#include "matrices/Matrix.h"
#include "matrices/Transform.h"
#include "scene/Canvas.h"
#include "VirtualCannon.h"
#include "shapes/Shape.h"
#include "rays/Ray.h"
#include "materials/Light.h"
#include "materials/Material.h"
#include "scene/World.h"


int main(){
    // CH 2 putting it all together
//    Vector v = Vector(1,1.8,0).normalize();
//     v*11.25;
//    Projectile p = Projectile(Point(0,1,0),v );
//    Environment e = Environment(Vector(0,-0.1, 0), Vector(0,-0.01,0));
//    Canvas c = Canvas(900,560);
//    int tick_count = 0;
//    double pos = p.get_position().y();
//     while (pos > 0){
//         p= tick(e, p);
//         pos = p.get_position().y();
//         tick_count += 1;
//         int posx = int(p.get_position().x());
//         int posy = c.height() - int(pos);
//         if (posx <= c.width() and posy <= c.height()){
//             c.write_pixel(posy, posx, Color(0,1,0));
//         }
//         std::cout << "position: (" << posx<< ", " << posy<<") tick_count: " << tick_count << std::endl;
//     }
//    std::ofstream out("ch2_output.ppm");
//    std::string ppm = c.canvas_to_ppm();
//    out << ppm;
//    out.close();

//  CH 4 putting all together
//    Canvas c = Canvas(800, 800);
//    double radius = c.width() * 3.0/8.0;
//    Matrix center_origin = Translation(c.width()/2.0, 0.0, c.height()/2.0);
//    for (int j = 0; j < 12; j++){
//        Point p = Rotation('y', j*M_PI/6.0) * Point(0.0,0.0,1.0);
//        p.setX(p.x() * radius);
//        p.setZ(p.z() * radius);
//        p = center_origin * p;
//        p.setZ(c.height() - (int) p.z()) ;
//        c.write_pixel((int)p.z(), (int)p.x(), Color(0,1,0));
//    }
//    std::ofstream out("ch4_output.ppm");
//    std::string ppm = c.canvas_to_ppm();
//    out << ppm;
//    out.close();

// CH 5 putting it together
//    Point ray_origin =Point(0,0,-5);
//    double wall_z = 10.0;
//    double wall_size = 7;
//    int canvas_pixels = 100;
//    double pixel_size = wall_size/canvas_pixels;
//    double half = wall_size/2;
//
//    Canvas c = Canvas(canvas_pixels, canvas_pixels);
//    Color color = Color(0,0,1);
//    Sphere shape = Sphere();
//    Matrix t = Scaling(0.5,1,1) * Shearing(1.0,0.0,0.0,0.0,0.0,0.0);
//    shape.setTransform(t);
//
//    for (int y = 0; y < canvas_pixels; y++){
//        double world_y = half - pixel_size*y;
//        for (int x = 0; x < canvas_pixels; x++){
//            double worldx = -half + pixel_size*x;
//            Point position = Point(worldx, world_y, wall_z);
//            Vector direction = position - ray_origin;
//            Ray r = Ray(ray_origin, direction.normalize());
//            IntersectList xs = r.intersects(shape);
//            if (xs.hit() != nullptr){
//                c.write_pixel(x, y, color);
//            }
//        }
//    }
//
//    std::ofstream out("ch5_output.ppm");
//    std::string ppm = c.canvas_to_ppm();
//    out << ppm;
//    out.close();

// ch6 putting it together
//    Point ray_origin =Point(0,0,-5);
//    double wall_z = 10.0;
//    double wall_size = 7;
//    int canvas_pixels = 100;
//    double pixel_size = wall_size/canvas_pixels;
//    double half = wall_size/2;
//
//    Canvas c = Canvas(canvas_pixels, canvas_pixels);
//    Color color = Color(0,0,1);
//    Sphere shape = Sphere();
//    Material m = Material();
//    m.setColor(Color(0,1,0));
//    shape.setMaterial(m);
//
//    Light light = Light(Point(-10, 10,-10), Color(1,1,1));
//
//    Matrix t = Scaling(0.5,1,1) * Shearing(1.0,0.0,0.0,0.0,0.0,0.0);
//    shape.setTransform(t);

//    for (int y = 0; y < canvas_pixels; y++){
//        double world_y = half - pixel_size*y;
//        for (int x = 0; x < canvas_pixels; x++){
//            double worldx = -half + pixel_size*x;
//            Point position = Point(worldx, world_y, wall_z);
//            Vector direction = position - ray_origin;
//            Ray r = Ray(ray_origin, direction.normalize());
//            IntersectList xs = r.intersects(shape);
//            Intersect* hit = xs.hit();
//            if (hit != nullptr){
//                Intersect h = *hit;
//                Point p = r.position(h.getT());
//                Vector n = h.getObject().normal_at(p);
//                Vector eye = -r.getDirection();
//                Color color = h.getObject().getMaterial().lighting(light, p, eye, n);
//                c.write_pixel(x, y, color);
//            }
//        }
//    }
//
//    std::ofstream out("ch6_output.ppm");
//    std::string ppm = c.canvas_to_ppm();
//    out << ppm;
//    out.close();


// Ch7 puttting it together
    Sphere floor = Sphere();
    floor.setTransform(Scaling(10, 0.01, 10));
    floor.setMaterial(Material(Color(1,0.9,0.9),0.1, 0.9, 0.0, 200));

    Sphere left_wall = Sphere();
    Matrix t_left = Translation(0,0,5) * Rotation('y',-M_PI_4) *  Rotation('x', M_PI_2) * Scaling(10, 0.01, 10);
    left_wall.setTransform(t_left);

    left_wall.setMaterial(floor.getMaterial());

    Sphere right_wall = Sphere();
    right_wall.setTransform(Translation(0,0,5) *
                            Rotation('y',M_PI_4) *
                            Rotation('x', M_PI_2) *
                            Scaling(10, 0.1, 10));
    right_wall.setMaterial(floor.getMaterial());

    Sphere middle = Sphere();
    right_wall.setTransform(Translation(-0.5,1.0,0.5));
    right_wall.setMaterial(Material(Color(0.1,1,0.5),0.1, 0.7, 0.3, 200));

    Sphere right = Sphere();
    right_wall.setTransform(Translation(1.5,0.5,-0.5) * Scaling(0.5, 0.5, 0.5));
    right_wall.setMaterial(Material(Color(0.5,1,0.1),0.1, 0.7, 0.3, 200));

    Sphere left = Sphere();
    right_wall.setTransform(Translation(-1.5,0.33,-0.75) * Scaling(0.33, 0.33, 0.33));
    right_wall.setMaterial(Material(Color(1.0,0.8,0.1),0.1, 0.7, 0.3, 200));

    World w = World();
    w.addLight(Light(Point(-10, 10, -10), Color(1,1,1)));
    w.addObject(left);
    w.addObject(right);
    w.addObject(middle);
    w.addObject(floor);
    w.addObject(left_wall);
    w.addObject(right_wall);



    Camera cam = Camera(100, 50, M_PI/3 );
    cam.setTransform(view_transform(Point(0,1.5, -5), Point(0,1,0), Vector(0,1,0)));

    Canvas img = cam.render(w);

    std::ofstream out("ch7_output.ppm");
    std::string ppm = img.canvas_to_ppm();
    out << ppm;
    out.close();


    return 0;
}
