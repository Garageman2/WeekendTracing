#pragma once

#include <cmath>
#include <memory>
#include <limits>

#include "Ray.h"
#include "Vector3.h"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double Infinity = std::numeric_limits<double>::infinity();
const double Pi = 3.1415926535897932385;

inline double DegreesToRadians(double Degrees)
{
    return Degrees*Pi/180;
}