#include <iostream>
#include <fstream>
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"

double HitSphere(const Point3& Center, double Radius, const Ray& r)
{
    Vec3 Oc = r.Origin() - Center;
    auto a = dot(r.Direction(),r.Direction());
    auto b =  2.0 * dot(Oc, r.Direction());
    auto c = dot(Oc,Oc) - Radius*Radius;
    auto Discriminant = b*b -4*a*c;
    if (Discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return(-b -sqrt(Discriminant)) / (2.0*a);
    }
}

Color RayColor(const Ray& r)
{
    auto t = HitSphere(Point3(0,0,-1),0.5,r);
    if(t>0.0)
    {
        Vec3 N = UnitVector(r.At(t)-Vec3(0,0,-1));
        return 0.5*Color(N.x()+1,N.y()+1,N.z()+1);
    }
    Vec3 UnitDirection = UnitVector(r.Direction());
    t = 0.5*(UnitDirection.y()+1.0);
    return (1.0-t)*Color(1.0,1.0,1.0)+ t*Color(0.5,0.7,1.0);
}

int main() {

    //basics
    const auto AspectRatio = 16/9;
    const int ImageWidth = 1024;
    const int ImageHeight = static_cast<int>(ImageWidth / AspectRatio);

    //Camera
    double ViewportHeight = 2.0;
    double ViewportWidth = 2.0;
    double FocalLength = 1.0;

    //extents
    Point3 Origin = Point3(0,0,0);
    Point3 Horizontal = Vec3(ViewportWidth,0,0);
    Point3 Vertical = Vec3(0,ViewportHeight,0);
    Point3 LowerLeftCorner = Origin-Horizontal/2 - Vertical/2 - Vec3(0,0,FocalLength);

    //Render
    std::ofstream OutputFile;
    OutputFile.open("Output.ppm");
    OutputFile<<"P3\n"<< ImageWidth << ' ' << ImageHeight << "\n255\n";

    for (int j = ImageHeight-1; j>=0; j--)
    {
        std::cout << "Writing line " << ImageHeight-j << std::endl;
        for(int i = 0; i < ImageWidth; i++)
        {
            double u = double(i) / ImageWidth;
            double v = double(j) / ImageHeight;
            Ray r(Origin,LowerLeftCorner+ u*Horizontal + v*Vertical - Origin);
            Color PixelColor = RayColor(r);
            WriteColor(OutputFile,PixelColor);
        }
    }

    OutputFile.close();

    return 0;
}
