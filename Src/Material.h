#pragma once

struct HitRecord;

#include "RTWeekend.h"



class Material
{
public:
    virtual bool Scatter(const Ray& r, const HitRecord& Rec, Color& Attenuation, Ray& Scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Color& A) : Albedo(A) {}

    virtual bool Scatter(const Ray& r, const HitRecord& Rec, Color& Attenuation, Ray& Scattered) const override;

public:
    Color Albedo;
};

class Metal : public Material{
public:
    Metal(const Color &A, double R) : Albedo(A), Roughness(R < 1 ? R : 1) {}

    virtual bool Scatter(const Ray &r, const HitRecord &Rec, Color &Attenuation, Ray &Scattered) const override;

public:
    Color Albedo;
    double Roughness;
};
bool Lambertian::Scatter(const Ray &r, const HitRecord &Rec, Color &Attenuation, Ray &Scattered) const
{
    auto ScatterDirection = Rec.Normal + RandomUnitVector();
    Scattered = Ray(Rec.P,ScatterDirection);

    if(ScatterDirection.NearZero())
    {ScatterDirection = Rec.Normal;}

    Attenuation = Albedo;
    return true;
}

bool Metal::Scatter(const Ray &r, const HitRecord &Rec, Color &Attenuation, Ray &Scattered) const
{
    Vec3 Reflected = Reflect(UnitVector(r.Direction()),Rec.Normal);
    Scattered = Ray(Rec.P,Reflected + Roughness*RandomInUnitSphere());
    Attenuation = Albedo;
    return (dot(Scattered.Direction(),Rec.Normal) > 0);
}