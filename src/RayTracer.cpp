#include <cmath>
#include <ctime>
#include <QApplication>
#include <include/RayTracer.h>
#include <include/Application.h>
#include <include/RenderParams.h>
#include <include/GUI/QSFMLCanvas.hpp>
#include <include/Scene.h>
#include <include/Events.h>
#include <include/Utility.h>
#include <include/Shapes.h>
#include <include/Shader.h>

RayTracer::RayTracer(const RenderParams &rp) {
   this->rp = &rp;
   image.loadFromFile("assets/hi_frog.jpg");
   //image.create(this->rp->getResolutionX(),this->rp->getResolutionY());
}

void RayTracer::init() {
   image = sf::Image();
   image.create(rp->pixelWidth,rp->pixelHeight);

   rayStart = rp->scene->mainCamera.getPos();
   Vector3D camRight = rp->scene->mainCamera.getForward().crossProduct(rp->scene->mainCamera.getUp()).normalize();
   lensWidthVec = camRight * rp->lensWidth;
   lensHeightVec = rp->scene->mainCamera.getUp() * rp->lensHeight;
   bottomLeft = (rayStart + rp->scene->mainCamera.getForward() * rp->focalLength) - (lensWidthVec/2.0) - (lensHeightVec/2.0);
   pixelWidthVec = lensWidthVec / rp->pixelWidth;
   pixelHeightVec = lensHeightVec / rp->pixelHeight;
   subPixelRows = pow(2,rp->subdivPerPixel);
   subPixelSize = pixelWidthVec.calcMagnitude()/subPixelRows;
   subPixelWidthVec = pixelWidthVec/subPixelRows;
   subPixelHeightVec = pixelHeightVec/subPixelRows;
}

Vector3D RayTracer::getPixelOrigin(unsigned int x, unsigned int y) {
   return (bottomLeft + pixelWidthVec*x + pixelHeightVec*y);
}

std::vector<Vector3D> RayTracer::getSamplePoints(unsigned int x, unsigned int y) {
   std::vector<Vector3D> samplePts;

   Vector3D pixOrigin = getPixelOrigin(x,y);
   for(int i=0; i<subPixelRows; i++) {
      for(int j=0; j<subPixelRows; j++) {
         Vector3D randXVec = subPixelWidthVec * j + (subPixelWidthVec*((double)rand() / RAND_MAX));
         Vector3D randYVec = subPixelHeightVec * i + (subPixelHeightVec*((double)rand() / RAND_MAX));
         samplePts.push_back(pixOrigin + randXVec + randYVec);
      }
   }
   return samplePts;
}

void RayTracer::run() {
   srand ( time(NULL) );

   Application* mainApp = Application::getInstance();
   QApplication::postEvent(mainApp, new QEvent(RayTraceEvent::traceStart));

   // Start tracing
   unsigned int numSamples = subPixelRows*subPixelRows;
   unsigned int numObjects = rp->scene->sceneObjects.size();
   unsigned int numLights = rp->scene->sceneLights.size();
   //------------------------ FOR EACH PIXEL ------------------------------------
   for(int y=0; y<rp->pixelHeight; y++) {
      int imageY = abs(y - (rp->pixelHeight-1)); // refactor so that the operation to get y isn't necessary???
      for(int x=0; x<rp->pixelWidth; x++) {
         std::vector<Vector3D> samplePts = getSamplePoints(x,y);
         std::vector<sf::Color> samples(numSamples);
         // -------------------- FOR EACH RAY -------------------------------
         for(int i=0; i<numSamples; i++) {
            // create ray
            Ray curRay = Ray(rayStart,samplePts[i]);
            double closest = INFINITY;
            for(int j=0; j<numObjects; j++) { // FOR EACH OBJECT
               Shape* curObject = rp->scene->sceneObjects[j];
               const Shader* curShader = curObject->getShader();
               Hit hit; // create Hit object to store hit info in
               if(curObject->intersection(curRay, &hit)) {  // if it intersects object
                  if(hit.distance < closest) {              // and it is the first object the ray hits
                     closest = hit.distance;
                     Vector3D intersectionPt = curRay.dir*hit.distance+curRay.src;
                     samples[i] = curShader->getColor(curRay, intersectionPt, curObject);
                  }
               }
            }
            if(closest == INFINITY) { // if there was no intersection for any object
               samples[i] = sf::Color(20,20,20); // put black
            }
         }
         // --------------------- END EACH RAY ---------------------------
         float totR=0, totG=0, totB=0;
         for(int i=0; i<numSamples; i++) { // average samples
            totR += samples[i].r;
            totG += samples[i].g;
            totB += samples[i].b;
         }
         image.setPixel(x,imageY,sf::Color(totR/(float)numSamples,totG/(float)numSamples,totB/(float)numSamples)); // put object color
         QApplication::postEvent(mainApp->SFMLView, new QEvent(RayTraceEvent::tracePixelFilled));
      }
   }

   QApplication::postEvent(mainApp, new QEvent(RayTraceEvent::traceEnd));
}
