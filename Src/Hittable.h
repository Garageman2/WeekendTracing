#pragma once

#include "Ray.h"

struct HitRecord
{
    Point3 P;
    Vec3 Normal;
    double t;
};

class Hittable
{
public:
    virtual bool Hit(const Ray& r, double t_Min, double t_Max, HitRecord& Rec) const = 0;
};