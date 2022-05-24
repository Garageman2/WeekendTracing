#include "Hittable.h"
#include "RTWeekend.h"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(Point3 Cen, double r, shared_ptr<Material> M) : Center(Cen), Radius(r), Mat_ptr(M) {};

    bool Hit(const Ray& r, double t_Min, double t_Max, HitRecord& Rec) const override;

public:
    Point3 Center;
    double Radius;
    shared_ptr<Material> Mat_ptr;
};