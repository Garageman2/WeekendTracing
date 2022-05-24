#pragma once

#include <cmath>
#include <memory>
#include <limits>
#include <random>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double Infinity = std::numeric_limits<double>::infinity();
const double Pi = 3.1415926535897932385;

inline double DegreesToRadians(double Degrees)
{
    return Degrees*Pi/180;
}

inline double RandomDouble()
{
    static std::uniform_real_distribution<double> Distribution(0.0,1.0);
    static std::mt19937 Generator;
    return Distribution(Generator);
}

inline double RandomDouble(double Min, double Max)
{
    return Min + (Max-Min)*RandomDouble();
}

inline double Clamp(double X, double Min, double Max)
{
    if(X < Min) {return Min;}
    if (X > Max) {return Max;}
    return X;
}

#include "Ray.h"
#include "Vector3.h"

