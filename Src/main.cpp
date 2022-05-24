#include <iostream>
#include <fstream>
#include "RTWeekend.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"

Color RayColor(const Ray& r, const Hittable& World)
{
    HitRecord Rec;
    if(World.Hit(r,0,Infinity,Rec))
    {
        //return Color(0.0,1.0,0.0);
        return 0.5 * (Rec.Normal + Color(1,1,1));
    }
    Vec3 UnitDirection  = UnitVector(r.Direction());
    auto t = 0.5*(UnitDirection.y() + 1.0);
    return (1.0-t)*Color(0.7,1.0,1.0) + t*Color(0.5,0.7,1.0);
}


int main() {

    //basics
    const double AspectRatio = 16.0 / 9.0;
    const int ImageWidth = 512;
    const int ImageHeight = static_cast<int>(512);

    //Camera
    double ViewportHeight = 2.0;
    double ViewportWidth = 2.0;
    double FocalLength = 1.0;

    //World
    HittableList World;
    World.Add(make_shared<Sphere>(Point3(0,0,-1),.5));
    World.Add(make_shared<Sphere>(Point3(0,-100.6,-1),100));

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
            Color PixelColor = RayColor(r,World);
            WriteColor(OutputFile,PixelColor);
        }
    }

    OutputFile.close();

    return 0;
}
