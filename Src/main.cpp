#include <iostream>
#include <fstream>
#include "RTWeekend.h"

#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Material.h"

//TODO: STBI PNG
//TODO: OPENGL IMPLEMENTATION
//TODO: RENDER TRIANGLES IN OGL THEN PROJECT
//TODO: OGL QUAD VIEW WITH IMGui
//TODO: ADD OIDN

Color RayColor(const Ray& r, const Hittable& World, int Depth)
{
    HitRecord Rec;

    if(Depth <= 0)
    {
        return Color(0,0,0);
    }


    if(World.Hit(r,0,Infinity,Rec))
    {
        Ray Scattered;
        Color Attenuation;
        if(Rec.Mat_ptr->Scatter(r,Rec,Attenuation,Scattered))
        {return Attenuation * RayColor(Scattered,World,Depth-1);}
        return Color(0,0,0);
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
    const int MaxDepth = 50;

    //Camera
    Camera Cam;

    //World
    HittableList World;

    auto MaterialGround = make_shared<Lambertian>(Color(0.8,0.8,0.0));
    auto MaterialCenter = make_shared<Lambertian>(Color(0.3,0.6,0.8));
    auto MaterialLeft = make_shared<Dielectric>(1.5);
    auto MaterialRight = make_shared<Metal>(Color(0.8,0.6,0.2),1.0);

    World.Add(make_shared<Sphere>(Point3(0.0,-100.5,-1.0),100.0,MaterialGround));
    World.Add(make_shared<Sphere>(Point3(0.0,0.0,-1.0),0.5,MaterialCenter));
    World.Add(make_shared<Sphere>(Point3(-1.0,0.0,-1.0),-0.5,MaterialLeft));
    World.Add(make_shared<Sphere>(Point3(1.0,0.0,-1.0),0.5,MaterialRight));

    //Render
    std::ofstream OutputFile;
    OutputFile.open("Output.ppm");
    OutputFile<<"P3\n"<< ImageWidth << ' ' << ImageHeight << "\n255\n";

    for (int j = ImageHeight-1; j>=0; j--)
    {
        std::cout << "Writing Line " << ImageHeight-j << " / " << ImageHeight << "\n";
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
