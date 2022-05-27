#pragma once
#include "HittableList.h"
#include "Vector3.h"

HittableList RandomScene();
Color RayColor(const Ray& r, const Hittable& World, int Depth);
void RayTrace(unsigned char* data, int &ImageWidth, int &ImageHeight);
void UpdateTex(unsigned char* data, int IWid, int IHei);
