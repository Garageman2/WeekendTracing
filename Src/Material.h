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

class Dielectric : public Material
{
public:
    Dielectric(double IndexOfRefraction) : IOR(IndexOfRefraction) {}

    virtual bool Scatter(const Ray &r, const HitRecord &Rec, Color &Attenuation, Ray &Scattered) const override;



public:
    double IOR;
private:
    inline static double Reflectance(double Cosine, double RefIdx)
    {
        auto r0 = (1-RefIdx) / (1+RefIdx);
        r0 = r0 * r0;
        return r0 + (1-r0)*pow((1-Cosine),5);
    }
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

bool Dielectric::Scatter(const Ray &r, const HitRecord &Rec, Color &Attenuation, Ray &Scattered) const
{
    Attenuation = Color(1.0,1.0,1.0);
    double RefractionRatio = Rec.FrontFace ? (1.0/IOR) : IOR;

    Vec3 UnitDirection = UnitVector(r.Direction());

    double CosTheta = fmin(dot(-UnitDirection,Rec.Normal),1.0);
    double SinTheta = sqrt(1.0 - CosTheta*CosTheta);

    bool CannotRefract = RefractionRatio *  SinTheta > 1.0;
    Vec3 Direction;

    if(CannotRefract)
    {
        Direction = Reflect(UnitDirection,Rec.Normal);
    }
    else
    {
        Direction = Refract(UnitDirection,Rec.Normal,RefractionRatio);
    }

    Scattered = Ray(Rec.P,Direction);
    return true;
}