//-------------------------------------------------
//------------- SHAPES.CPP ------------------------
//-------------------------------------------------
//#include "stdafx.h"
#include <cmath>
#include <include/Shapes.h>

/*
Equation of a sphere with center at (x0,y0,z0) and radius r:
(x - x0)^2 + (y - y0)^2 _ (z - z0)^2 = r^2
*/
Vector3D Sphere::getNormal(const Vector3D& p) const {
   return Vector3D((p - pos)/radius);
}

bool Sphere::intersection(const Ray& r, Hit* h) const {
   Vector3D centerToRaySrc = r.src - pos;

   // If r.dir is a unit vector, "A" will always be 1 so you don't need to use it

   double b = 2 * centerToRaySrc.dotProduct(r.dir);
   //if(b < 0) return false; // sphere is behind the camera

   // C = (X0 - Xc)^2 + (Y0 - Yc)^2 + (Z0 - Zc)^2 - Sr^2
   double c = centerToRaySrc.dotProduct(centerToRaySrc) - radius*radius;

   double disc = b*b - 4*c;
   if(disc < 0) return false; // if discriminant is less than 0, there are no real roots

   double discSq = sqrt(disc);

   h->distance = (-b - discSq)/2.0;
   if(h->distance < 0) h->distance = (-b + discSq)/2.0;
   if(h->distance < 0) return false;
   return true;
}

bool Plane::intersection(const Ray& r, Hit* h) const {
   Vector3D cameraToPlane = pos - r.src;

   h->distance = (normal.dotProduct(cameraToPlane))/(normal.dotProduct(r.dir));
   if(h->distance < 0) return false;
   return true;
}
