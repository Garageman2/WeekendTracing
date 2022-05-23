#include <iostream>
#include <fstream>
#include "Vector3.h"
#include "Color.h"

int main() {

    //basics
    const int ImageWidth = 512;
    const int ImageHeight = 512;

    //Render
    std::ofstream OutputFile;
    OutputFile.open("Output.ppm");
    OutputFile<<"P3\n"<< ImageWidth << ' ' << ImageHeight << "\n255\n";

    for (int j = ImageHeight-1; j>=0; j--)
    {
        std::cout << "Writing line " << ImageHeight-j << std::endl;
        for(int i = 0; i < ImageWidth; i++)
        {
            Color PixelColor(double(i)/(ImageWidth),(double(j)/ImageHeight),.5);
            WriteColor(OutputFile,PixelColor);
        }
    }

    OutputFile.close();

    return 0;
}
