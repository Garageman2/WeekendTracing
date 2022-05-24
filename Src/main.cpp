#include <iostream>
#include <fstream>
#include "RTWeekend.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"

Color RayColor(const Ray& r, const Hittable& World)
{
    HitRecord Rec;
<<<<<<< Updated upstream
    if(World.Hit(r,0,Infinity,Rec))
    {
        //return Color(0.0,1.0,0.0);
        return 0.5 * (Rec.Normal + Color(1,1,1));
=======

    if(Depth <= 0)
    {
        return Color(0,0,0);
    }

   // if (World.Hit(r,0.001, Infinity, Rec)) {}

    if(World.Hit(r,0,Infinity,Rec))
    {
        Ray Scattered;
        Color Attenuation;
        if(Rec.Mat_ptr->Scatter(r,Rec,Attenuation,Scattered))
        {return Attenuation * RayColor(Scattered,World,Depth-1);}
        else
        {return Color(Rec.Normal);}
>>>>>>> Stashed changes
    }
    Vec3 UnitDirection  = UnitVector(r.Direction());
    auto t = 0.5*(UnitDirection.y() + 1.0);
    return (1.0-t)*Color(0.7,1.0,1.0) + t*Color(0.5,0.7,1.0);
}


int main() {

    //basics
    const double AspectRatio = 16.0 / 9.0;
<<<<<<< Updated upstream
    const int ImageWidth = 512;
    const int ImageHeight = static_cast<int>(512);
=======
    const int ImageWidth = 256;
    const int ImageHeight = static_cast<int>(ImageWidth / AspectRatio);
    const int SamplesPerPixel = 100;
    const int MaxDepth = 25;
>>>>>>> Stashed changes

    //Camera
    double ViewportHeight = 2.0;
    double ViewportWidth = 2.0;
    double FocalLength = 1.0;

    //World
    HittableList World;
    World.Add(make_shared<Sphere>(Point3(0,0,-1),.5));
    World.Add(make_shared<Sphere>(Point3(0,-100.6,-1),100));

<<<<<<< Updated upstream
    //extents
    Point3 Origin = Point3(0,0,0);
    Point3 Horizontal = Vec3(ViewportWidth,0,0);
    Point3 Vertical = Vec3(0,ViewportHeight,0);
    Point3 LowerLeftCorner = Origin-Horizontal/2 - Vertical/2 - Vec3(0,0,FocalLength);
=======
    auto MaterialGround = make_shared<Lambertian>(Color(0.8,0.8,0.0));
    auto MaterialCenter = make_shared<Dielectric>(1.5);
    auto MaterialLeft = make_shared<Dielectric>(1.5);
    auto MaterialRight = make_shared<Metal>(Color(0.8,0.6,0.2),1.0);

    World.Add(make_shared<Sphere>(Point3(0.0,-100.5,-1.0),100.0,MaterialGround));
    World.Add(make_shared<Sphere>(Point3(0.0,0.0,-1.0),0.5,MaterialCenter));
    World.Add(make_shared<Sphere>(Point3(-1.0,0.0,-1.0),0.5,MaterialLeft));
    World.Add(make_shared<Sphere>(Point3(1.0,0.0,-1.0),0.5,MaterialRight));
>>>>>>> Stashed changes

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
            Color PixelColor = RayColor(r,World);
            WriteColor(OutputFile,PixelColor);
        }
    }

    OutputFile.close();

    return 0;
}
