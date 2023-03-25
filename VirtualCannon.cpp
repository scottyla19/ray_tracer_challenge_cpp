#include "VirtualCannon.h"
#include "primitives/Tuple.h"
#include <iostream>

Projectile::Projectile(const Point& p = Point(0.0f,0.0f,0.0f), const Vector& v = Vector(0.0f,0.0f,0.0f)):
    m_position {p},
    m_velocity {v}
{
}


Environment::Environment(const Vector& gravity = Vector(0.0f,0.0f,0.0f), const Vector& wind = Vector(0.0f,0.0f,0.0f)):
    m_gravity {gravity},
    m_wind {wind}
{
}

Projectile tick(Environment env, Projectile proj){
    Tuple velo = proj.get_velocity() + env.get_gravity() + env.get_wind();
    Tuple pos = proj.get_position() + proj.get_velocity();
    return Projectile(pos, velo);
}
