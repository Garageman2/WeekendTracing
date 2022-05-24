#pragma once
#include "Vector3.h"
#include <iostream>

void WriteColor(std::ostream &out, Color PixelColor, int SamplesPerPixel)
{
    double R = PixelColor.x();
    double G = PixelColor.y();
    double B = PixelColor.z();

    double Scale = 1.0 / SamplesPerPixel;
    R = sqrt(sqrt(Scale * R));
    G = sqrt(sqrt(Scale * G));
    B = sqrt(sqrt(Scale * B));

    out <<static_cast<int>(255.999 * Clamp(R,0.0,0.999))<< ' '
        <<static_cast<int>(255.999 * Clamp(G,0.0,0.999))<< ' '
        <<static_cast<int>(255.999 * Clamp(B,0.0,0.999))<< '\n';
}