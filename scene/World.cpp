#include "World.h"


World::World(){

}

World::World(bool isDefault = false)
{
    if (isDefault){
        Light light = Light(Point(-10,10,-10), Color(1,1,1));
        Sphere s1 = Sphere();
        Material mat = Material();
        mat.setColor(Color(0.8,1.0,0.6));
        mat.setDiffuse(0.7);
        mat.setSpecular(0.2);
        s1.setMaterial(mat);
        Sphere s2 = Sphere();
        s2.setTransform(Scaling(0.5,0.5,0.5));
        m_lights.push_back(light);
        m_objects.push_back(s1);
        m_objects.push_back(s2);
    }
}

IntersectList World::intersect_world(Ray r)const {
    IntersectList il = IntersectList();
    std::vector<IntersectList> world_intersects ;
    for (int i = 0; i < m_objects.size(); i++ ){
        world_intersects.push_back(r.intersects(m_objects[i]));
    }
    for (int j = 0; j < world_intersects.size(); j++){
        for(int k = 0; k < world_intersects[j].getCount(); k++){
            il.appendIntersect(world_intersects[j][k]);
        }
    }

    return il;
}

void World::replaceLightAt(const Light& newLight, int index)
{
    m_lights[index] = newLight;
}

void World::replaceObjectAt(const Shape& newShape, int index)
{
    m_objects[index] = newShape;
}


Color World::shade_hit(const Computation& comps) const{
// only returning first light from getLights eventually could loop throught all lights and combine colors but too computationally expensive on laptop.
    return comps.getObject().getMaterial().lighting(m_lights[0],
                                                    comps.getPoint(),
                                                    comps.getEyev(),
                                                    comps.getNormalv());
}

Color World::color_at(const Ray& ray) const
{
    IntersectList intersects = intersect_world(ray);
    Intersect* hit = intersects.hit();
    if (hit == nullptr){
        return Color(0,0,0);
    }
    Intersect h = *hit;
    Computation comps = Computation(h, ray);
    return shade_hit(comps);
}

Camera::Camera(int hsize, int vsize, double field_of_view):
m_hsize{hsize},
m_vsize{vsize},
m_field_of_view{field_of_view},
m_transform{Matrix(4,4)}
{
    double half_view = tan(m_field_of_view / 2);
    double aspect = (double)m_hsize/m_vsize;
    if (aspect >= 1){
        m_half_width = half_view;
        m_half_height = half_view / aspect;
    }else{
        m_half_width = half_view * aspect;
        m_half_height = half_view;
    }
    m_pixel_size = (m_half_width * 2)/m_hsize;
}

Ray Camera::ray_for_pixel(int px, int py)
{
    double xoffset = (px + 0.5) * m_pixel_size;
    double yoffset = (py + 0.5) * m_pixel_size;

    double world_x = m_half_width - xoffset;
    double world_y = m_half_height - yoffset;

    Point pixel = m_transform.inverse() * Point(world_x, world_y, -1);
    Point origin = m_transform.inverse() * Point(0,0,0);
    Vector direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}

Canvas Camera::render(const World& w)
{
    Canvas image = Canvas(m_hsize, m_vsize);
    for (int y = 0; y < m_vsize; y++){
        for (int x = 0; x < m_hsize; x++){
            Ray r = ray_for_pixel(x, y);
            Color color = w.color_at(r);
            image.write_pixel(y,x, color);
        }
    }
    return image;
}

