#include "Camera.h"

Ray Camera::GetRay(double U, double V) const
{
    return Ray(Origin, LowerLeftCorner + U*Horizontal + V*Vertical - Origin);
}