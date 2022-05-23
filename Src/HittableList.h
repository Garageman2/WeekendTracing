#pragma once
#include "Hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> Object) {Add(Object);}

    void Clear() {Objects.clear();}
    void Add(shared_ptr<Hittable> Object) {Objects.push_back(Object);}

    virtual bool Hit(const Ray& r, double t_Min, double t_Max, HitRecord& Rec) const override;

public:
    std::vector<shared_ptr<Hittable>> Objects;
};

