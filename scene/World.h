#ifndef RTC_WORLD
#define RTC_WORLD
#include <vector>
#include <ostream>
#include <cmath>

#include "../shapes/Shape.h"
#include "../materials/Light.h"
#include "../matrices/Transform.h"
#include "../rays/Ray.h"
#include "../primitives/Color.h"
#include "../rays/Computation.h"
#include "Canvas.h"

class World {
private:
    std::vector<Shape> m_objects;
    std::vector<Light> m_lights;



public:
    World();
    World(bool isDefault);


    // accessors
    const std::vector<Shape>& getObjects()const {return m_objects;}
    const std::vector<Light>& getLights()const{return m_lights;}
    void addObject(const Shape& obj) {m_objects.push_back(obj);}
    void addLight(const Light& light) {m_lights.push_back(light);}
    void replaceObjectAt(const Shape& newShape, int index);
    void replaceLightAt(const Light& newLight, int index);

    // member functions
    IntersectList intersect_world(Ray r) const;
    Color shade_hit(const Computation& comps)const;
    Color color_at(const Ray& ray) const;


    ~World() = default;

};


class Camera{
private:
    int m_hsize;
    int m_vsize;
    double m_field_of_view;
    Matrix m_transform;
    double m_pixel_size;
    double m_half_width;
    double m_half_height;

public:
    Camera(int hsize, int vsize, double field_of_view);

    const int getHsize()const { return m_hsize;}
    const int getVsize()const { return m_vsize;}
    const double getField_of_view()const { return m_field_of_view;}
    const double getPixel_size()const {return m_pixel_size;}
    const Matrix getTransform()const {return m_transform;}
    void setTransform(Matrix t) {m_transform = t;}

    Ray ray_for_pixel(int px, int py);
    Canvas render(const World& w);

    ~Camera() = default;

};






#endif
