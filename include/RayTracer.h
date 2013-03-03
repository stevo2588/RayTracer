#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QThread>
#include <SFML/Graphics.hpp>
#include <include/Utility.h>

// RAYTRACER

class RenderParams;
class Scene;

class RayTracer : public QThread {
   Q_OBJECT
public:
   RayTracer(const RenderParams &rp);
   void run();
   sf::Image* getImage() { return &image; }
   void init();

private:
   Vector3D getPixelOrigin(unsigned int x, unsigned int y);
   std::vector<Vector3D> getSamplePoints(unsigned int x, unsigned int y);

   sf::Image image;
   const RenderParams *rp;

   Vector3D rayStart;
   Vector3D lensWidthVec;
   Vector3D lensHeightVec;
   Vector3D bottomLeft;

   Vector3D pixelWidthVec;
   Vector3D pixelHeightVec;
   unsigned int subPixelRows;
   double subPixelSize;
   Vector3D subPixelWidthVec;
   Vector3D subPixelHeightVec;
};

#endif // RAYTRACER_H
