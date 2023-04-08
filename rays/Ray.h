#ifndef RTC_RAY
#define RTC_RAY

#include <vector>

#include "Intersect.h"
#include "../primitives/Tuple.h"
#include "../primitives/constants.h"
#include "../shapes/Shape.h"
#include "../matrices/Matrix.h"

class Ray
{
private:
    Point m_origin;
    Vector m_direction;
public:
    Ray(Point origin, Vector direction);

    // accessors
    Point getOrigin(){return m_origin;;}
    Vector getDirection(){return m_direction;}

    // member functions
    Point position(double t);
    IntersectList intersects(Shape s);
    Ray transform(Matrix t);

    ~Ray() = default;
};




#endif
