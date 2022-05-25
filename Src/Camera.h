#pragma once
#include "RTWeekend.h"

class Camera
{
public:
    Camera(Point3 LookFrom, Point3 LookAt, Vec3 VUp, double VFOV, double AspectRatio, double Aperture, double FocusDist)
    {
        auto Theta = DegreesToRadians(VFOV);
        auto H = tan(Theta/2);
        double ViewportHeight = 2.0 * H;
        double ViewportWidth = AspectRatio * ViewportHeight;
        double FocalLength = 1.0;

        W = UnitVector(LookFrom-LookAt);
        U = UnitVector(Cross(VUp,W));
        V = Cross(W,U);

        Origin = LookFrom;
        Horizontal = FocusDist * ViewportWidth * U;
        Vertical = FocusDist * ViewportHeight * V;
        LowerLeftCorner = Origin - Horizontal/2 - Vertical/2 - FocusDist*W;

        LensRadius = Aperture/2;

    }

    Ray GetRay(double S, double T) const;

private:
    Point3 Origin;
    Point3 LowerLeftCorner;
    Vec3 Horizontal;
    Vec3 Vertical;
    Vec3 U,V,W;
    double LensRadius;
};
