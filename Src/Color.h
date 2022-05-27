#pragma once
#include "Vector3.h"
#include <iostream>



void WriteColor(unsigned char* Data, Color PixelColor, int SamplesPerPixel, int Index)
{
    Index *= 3;

    double R = PixelColor.x();
    double G = PixelColor.y();
    double B = PixelColor.z();

    double Scale = 1.0 / SamplesPerPixel;
    R = sqrt(sqrt(Scale * R));
    G = sqrt(sqrt(Scale * G));
    B = sqrt(sqrt(Scale * B));

    Data[Index]   = static_cast<int>(255.999 * Clamp(R,0.0,0.999));
    Data[Index+1] = static_cast<int>(255.999 * Clamp(G,0.0,0.999));
    Data[Index+2] = static_cast<int>(255.999 * Clamp(B,0.0,0.999));

}
