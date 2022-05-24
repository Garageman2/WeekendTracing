#pragma once
#include "RTWeekend.h"

class Camera
{
public:
    Camera()
    {
        double AspectRatio = 16.0/9.0;
        double ViewportHeight = 2.0;
        double ViewportWidth = AspectRatio * ViewportHeight;
        double FocalLength = 1.0;

        Origin = Point3(0,0,0);
        Horizontal = Vec3(ViewportWidth,0.0,0.0);
        Vertical = Vec3(0.0,ViewportHeight,0.0);
        LowerLeftCorner = Origin - Horizontal/2 - Vertical/2 - Vec3(0,0,FocalLength);
    }

    Ray GetRay(double U, double V) const;

private:
    Point3 Origin;
    Point3 LowerLeftCorner;
    Vec3 Horizontal;
    Vec3 Vertical;
};
