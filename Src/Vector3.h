#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3
{
public:
    Vec3() : e{0,0,0} {}
    Vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

    double x() const { return e[0];}
    double y() const { return e[1];}
    double z() const { return e[2];}

    Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]);}
    double operator[](int i) const {return e[i];}
    double& operator[](int i) {return e[i];}

    Vec3& operator+=(const Vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3& operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& operator/=(const double t)
    {return *this *= 1/t;}

    double Length() const
    {
        return sqrt(LengthSquared());
    }

    double LengthSquared() const
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline static Vec3 Random()
    {
        return Vec3(RandomDouble(),RandomDouble(),RandomDouble());
    }

    inline static Vec3 Random(double Min, double Max)
    {
        return Vec3(RandomDouble(Min,Max),RandomDouble(Min,Max),RandomDouble(Min,Max));
    }

    inline bool NearZero()
    {
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

public:
    double e[3];

};

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.e[0] << " " << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[0]+v.e[0],u.e[1]+v.e[1],u.e[2]+v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[0]-v.e[0],u.e[1]-v.e[1],u.e[2]-v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[0]*v.e[0],u.e[1]*v.e[1],u.e[2]*v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v)
{
    return Vec3(t*v.e[0],t*v.e[1],t*v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t)
{
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t)
{
    return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v)
{
    return u.e[0] * v.e[0] +
           u.e[1] * v.e[1] +
           u.e[2] * v.e[2];
}

inline Vec3 Cross(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 UnitVector(Vec3 v)
{
    return v/v.Length();
}

inline Vec3 RandomInUnitSphere()
{
    while(true)
    {
        Vec3 P = Vec3::Random(-1,1);
        if(P.LengthSquared()>=1) continue;
        return P;
    }
}

inline Vec3 RandomUnitVector()
{
    return UnitVector(RandomInUnitSphere());
}

inline Vec3 RandomInHemisphere(const Vec3& Normal)
{
    Vec3 InUSphere = RandomInUnitSphere();
    if(dot(InUSphere,Normal) > 0.0)
    {
        return InUSphere;
    }
    else
    {
        return -InUSphere;
    }
}

inline Vec3 Reflect(const Vec3& v, const Vec3& n)
{
    return v - 2*dot(v,n)*n;
}

inline Vec3 Refract(const Vec3& uv, const Vec3& n, double EtaiOverEtat)
{
    auto CosTheta = fmin(dot(-uv,n),1.0);
    Vec3 ROutPerp = EtaiOverEtat * (uv + CosTheta * n);
    Vec3 ROutParallel = -sqrt(fabs(1.0-ROutPerp.LengthSquared())) * n;
    return ROutPerp + ROutParallel;
}

inline Vec3 RandomInUnitDisk()
{
    while(true)
    {
        auto P = Vec3(RandomDouble(-1,1),RandomDouble(-1,1),0);
        if(P.LengthSquared()>=1) { continue;}
        return P;
    }
}
