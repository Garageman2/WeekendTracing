#include "Camera.h"

Ray Camera::GetRay(double S, double T) const
{
    Vec3 Rd = LensRadius * RandomInUnitDisk();
    Vec3 Offset = U * Rd.x() + V * Rd.y();
    return Ray(Origin + Offset, LowerLeftCorner + S*Horizontal + T*Vertical - Origin - Offset);
}