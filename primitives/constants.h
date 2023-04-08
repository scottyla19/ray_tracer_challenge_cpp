#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <cmath>


    inline constexpr double ABS_EPSILON = 0.000000001;
    inline constexpr double REL_EPSILON = 0.0001;
    inline bool floatEqual(double a, double b, double absEpsilon = ABS_EPSILON, double relEpsilon = REL_EPSILON)
    {
        double diff{ std::abs(a - b) };
        if (diff <= absEpsilon)
            return true;

        return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
    }


#endif
