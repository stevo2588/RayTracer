#include <vector>
#include <include/RenderParams.h>
#include <include/Application.h>
#include <include/Shapes.h>
#include <include/Camera.h>
#include <include/Scene.h>

void RenderParams::setScene(std::string filename) {
   sceneName = filename;
   if(filename == "") { // set to the example scene
      //scene = &Scene::exampleScene;
      scene = new Scene();
   }
   else {

   }
}

void RenderParams::setResolutionX(unsigned int width) {
   double lensPixRatio = lensWidth/width;
   lensHeight = pixelHeight * lensPixRatio;
   pixelWidth = width;
}
void RenderParams::setResolutionY(unsigned int height) {
   double lensPixRatio = lensWidth/pixelWidth;
   lensHeight = height * lensPixRatio;
   pixelHeight = height;
}
void RenderParams::setLensWidth(double width) {
   lensWidth = width;
   lensHeight = pixelHeight * (lensWidth / pixelWidth);
}
void RenderParams::setFocalLength(double length) {
   focalLength = length;
}
void RenderParams::setSubDiv(unsigned int subdiv){
   subdivPerPixel = subdiv;
}
void RenderParams::setTraceDepth(unsigned int depth) {
   traceDepth = depth;
}
