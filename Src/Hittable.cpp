#include "Hittable.h"


void HitRecord::SetFaceNormal(const Ray& r, const Vec3& OutwardNormal)
{
    FrontFace = dot(r.Direction(),OutwardNormal);
    Normal = FrontFace ? OutwardNormal : -OutwardNormal;
}
