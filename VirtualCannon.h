#ifndef RTC_CANNON
#define RTC_CANNON
#include "primitives/Tuple.h"
#include <iostream>


class Projectile
{
private:
    Point m_position;
    Vector m_velocity;
public:
    Projectile(const Point& p, const Vector& v);

    Tuple get_position()const {return m_position;}
    Tuple get_velocity()const {return m_velocity;}
    void set_Tuple(Tuple p) {m_position = p;}
    void set_velocity(Tuple v) {m_velocity = v;}
    ~Projectile() = default;
};

class Environment
{
private:
    Vector m_wind;
    Vector m_gravity;
public:
    Environment(const Vector& gravity, const Vector& wind);
    Tuple get_gravity()const {return m_gravity;}
    Tuple get_wind()const {return m_wind;}
    void set_gravity(Tuple g) {m_gravity = g;}
    void set_wind(Tuple w) {m_wind = w;}
    ~Environment() = default;
};

Projectile tick(Environment env, Projectile proj);
#endif


