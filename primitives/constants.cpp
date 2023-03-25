#include <cmath>
#include "constants.h"

bool floatEqual(double a, double b, double absEpsilon = ABS_EPSILON, double relEpsilon = REL_EPSILON)
{
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    double diff{ std::abs(a - b) };
    if (diff <= absEpsilon)
        return true;

    // Otherwise fall back to Knuth's algorithm
    return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}