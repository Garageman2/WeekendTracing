#pragma once
#include "Vector3.h"
#include <iostream>

void WriteColor(std::ostream &out, Color PixelColor)
{
    out <<static_cast<int>(255.999 * PixelColor.x())<< ' '
        <<static_cast<int>(255.999 * PixelColor.y())<< ' '
        <<static_cast<int>(255.999 * PixelColor.z())<< '\n';
}