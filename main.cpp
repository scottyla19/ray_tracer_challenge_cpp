#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include "primitives/Tuple.h"
#include "primitives/constants.h"
#include "primitives/Matrix.h"
#include "matrices/Transform.h"
#include "scene/Canvas.h"
#include "VirtualCannon.h"

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
    Canvas c = Canvas(800, 800);
    double radius = c.width() * 3.0/8.0;
    Matrix center_origin = Translation(c.width()/2.0, 0.0, c.height()/2.0);
    for (int j = 0; j < 12; j++){
        Point p = Rotation('y', j*M_PI/6.0) * Point(0.0,0.0,1.0);
        p.setX(p.x() * radius);
        p.setZ(p.z() * radius);
        p = center_origin * p;
        p.setZ(c.height() - (int) p.z()) ;
        c.write_pixel((int)p.z(), (int)p.x(), Color(0,1,0));
    }
    std::ofstream out("ch4_output.ppm");
    std::string ppm = c.canvas_to_ppm();
    out << ppm;
    out.close();
    return 0;
}
