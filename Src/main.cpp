#include <iostream>
#include <fstream>
#include "RTWeekend.h"

#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"



Color RayColor(const Ray& r, const Hittable& World, int Depth)
{
    HitRecord Rec;

    if(Depth <= 0)
    {
        return Color(0,0,0);
    }

    if (World.Hit(r,0.001, Infinity, Rec)) {}

    if(World.Hit(r,0,Infinity,Rec))
    {
        Point3 Target = Rec.P + RandomInHemisphere(Rec.Normal);
        return 0.5 * RayColor(Ray(Rec.P, Target-Rec.P),World, Depth-1);
    }
    Vec3 UnitDirection  = UnitVector(r.Direction());
    auto t = 0.5*(UnitDirection.y() + 1.0);
    return (1.0-t)*Color(0.7,1.0,1.0) + t*Color(0.5,0.7,1.0);
}


int main() {

    //basics
    const double AspectRatio = 16.0 / 9.0;
    const int ImageWidth = 256;
    const int ImageHeight = static_cast<int>(ImageWidth / AspectRatio);
    const int SamplesPerPixel = 100;
    const int MaxDepth = 5;

    //Camera
    Camera Cam;

    //World
    HittableList World;
    World.Add(make_shared<Sphere>(Point3(0,0,-1),.5));
    World.Add(make_shared<Sphere>(Point3(0,-100.6,-1),100));
    //World.Add(make_shared<Sphere>(Point3(1,1,-1),.5));

    //Render
    std::ofstream OutputFile;
    OutputFile.open("Output.ppm");
    OutputFile<<"P3\n"<< ImageWidth << ' ' << ImageHeight << "\n255\n";

    for (int j = ImageHeight-1; j>=0; j--)
    {
        std::cout << "Writing line " << ImageHeight-j << std::endl;
        for(int i = 0; i < ImageWidth; i++)
        {
            Color PixelColor(0,0,0);
            for (int s = 0; s < SamplesPerPixel; ++s)
            {
                auto U = ((i + RandomDouble()) / ImageWidth);
                auto V = ((j + RandomDouble()) / ImageHeight);
                Ray R = Cam.GetRay(U,V);
                PixelColor += RayColor(R, World, MaxDepth);
            }
            WriteColor(OutputFile,PixelColor,SamplesPerPixel);
        }
    }

    OutputFile.close();

    return 0;
}
