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

HittableList RandomScene()
{
    HittableList World;

    auto GroundMaterial = make_shared<Lambertian>(Color(0.5,0.5,0.5));
    World.Add(make_shared<Sphere>(Point3(0,-1000,0),1000,GroundMaterial));

    for(int A = -11; A < 11; A++)
    {
        for(int B = -11; B < 11; B++)
        {
            double ChooseMat = RandomDouble();
            Point3 Center(A + 0.9*RandomDouble(),0.2,B+0.9*RandomDouble());

            if((Center-Point3(4.0,0.2,0.0)).Length() > 0.9)
            {
                shared_ptr<Material> SphereMaterial;

                if(ChooseMat < 0.8)
                {
                    //Diffuse
                    auto Albedo = Color::Random() * Color::Random();
                    SphereMaterial = make_shared<Lambertian>(Albedo);
                    World.Add(make_shared<Sphere>(Center,0.2,SphereMaterial));
                }

                else if(ChooseMat < .95)
                {
                    auto Albedo = Color::Random(0.5,1.0);
                    auto Roughness = RandomDouble(0,0.5);
                    SphereMaterial = make_shared<Metal>(Albedo,Roughness);
                    World.Add(make_shared<Sphere>(Center,0.2,SphereMaterial));
                }
                else
                {
                    SphereMaterial = make_shared<Dielectric>(1.333);
                    World.Add(make_shared<Sphere>(Center,0.2,SphereMaterial));
                }

            }
        }
    }

    auto Mat1 = make_shared<Dielectric>(1.333);
    World.Add(make_shared<Sphere>(Point3(0.0,1.0,0.0),1.0,Mat1));

    auto Mat2 = make_shared<Lambertian>(Color(0.4,0.2,0.1));
    World.Add(make_shared<Sphere>(Point3(-4.0,1.0,0.0),1.0,Mat2));

    auto Mat3 = make_shared<Metal>(Color(0.7,0.6,0.5),0.0);
    World.Add(make_shared<Sphere>(Point3(4.0,1.0,0.0),1.0,Mat3));

    return World;

}

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
    const double AspectRatio = 3.0/2.0;
    const int ImageWidth = 1200;
    const int ImageHeight = static_cast<int>(ImageWidth / AspectRatio);
    const int SamplesPerPixel = 500;
    const int MaxDepth = 50;

    //Camera
    auto R = cos(Pi/4);
    Point3 LookFrom(13,2,3);
    Point3 LookAt(0,0,0);
    Vec3 VUp(0,1,0);
    auto DistToFocus = 10.0;
    auto Aperture = 0.1;

    Camera Cam(LookFrom,LookAt,VUp,20.0,AspectRatio,Aperture,DistToFocus);

    //World
    auto World = RandomScene();

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
