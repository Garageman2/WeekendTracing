#include "Hittable.h"
#include "Vector3.h"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(Point3 Cen, double r) : Center(Cen), Radius(r) {};

    virtual bool Hit(const Ray& r, double t_Min, double t_Max, HitRecord& Rec) const override;
public:
    Point3 Center;
    double Radius;
};