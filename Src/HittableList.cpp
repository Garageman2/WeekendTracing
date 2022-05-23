#include "HittableList.h"

bool HittableList::Hit(const Ray &r, double t_Min, double t_Max, HitRecord &Rec) const
{
    HitRecord TempRec;
    bool HitAnything = false;
    auto Closest = t_Max;

    for(const auto& Object : Objects)
    {
        if(Object->Hit(r,t_Min,Closest,TempRec))
        {
            HitAnything = true;
            Closest = TempRec.t;
            Rec = TempRec;
        }
    }
    return HitAnything;
}