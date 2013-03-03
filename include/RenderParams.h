#ifndef RENDERPARAMS_H
#define RENDERPARAMS_H

#include <string>
#include <include/Scene.h>

class RenderParams {
public:
   RenderParams() {}
   void setScene(std::string filename);
   void setResolutionX(unsigned int width);
   void setResolutionY(unsigned int height);
   void setLensWidth(double width);
   void setFocalLength(double length);
   //void setRayNum(unsigned int num);
   void setSubDiv(unsigned int subdiv);
   void setTraceDepth(unsigned int depth);

   const Scene* getScene() { return scene; }
   std::string getSceneName() {return sceneName;}
   unsigned int getResolutionX() const {return pixelWidth;}
   unsigned int getResolutionY() const {return pixelHeight;}
   double getLensWidth() const {return lensWidth;}
   double getFocalLength() const {return focalLength;}
   unsigned int getSubDiv() const {return subdivPerPixel;}
   unsigned int getTraceDepth() const {return traceDepth;}

   friend class RayTracer;

private:
   const Scene* scene;
   std::string sceneName;

   unsigned int pixelWidth;
   unsigned int pixelHeight;

   float lensWidth;
   float lensHeight;
   float focalLength;

   //unsigned int raysPerPixel;
   unsigned int subdivPerPixel;
   unsigned int traceDepth;
};


#endif // RENDERPARAMS_H
