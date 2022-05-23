#pragma once
#include "Vector3.h"

class Ray
{
public:
    Ray(){}
    Ray(const Point3& Origin, const Vec3& Direction)
        :Orig(Origin),Dir(Direction) {}

    Point3 Origin() const {return Orig;}
    Vec3 Direction() const {return Dir;}

    Point3 At(double t) const
    {
        return Orig + t*Dir;
    }

public:
    Point3 Orig;
    Vec3 Dir;
};