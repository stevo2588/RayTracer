#include <cmath>
#include <include/Shader.h>
#include <include/Shapes.h>
#include <include/Light.h>

Shader::Shader(const std::vector<Light*>& lights, const Camera& activeCamera)
   : lights(lights), activeCamera(activeCamera)
{
}

PhongShader::PhongShader(sf::Color c, const std::vector<Light*>& lights, const Camera& activeCamera)
   : Shader(lights,activeCamera)
{
   diffuse.r = c.r;
   diffuse.g = c.g;
   diffuse.b = c.b;
}

sf::Color PhongShader::getColor(const Ray& r, const Vector3D& p, const Shape * sh) const {
   float maxColorValue = 10.0;

   unsigned int numLights = lights.size();
   Vector3D normal = sh->getNormal(p).normalize();
   double shininess = 90.0;
   HiDefColor totCol(0,0,0);
   //-------------------- FOR EACH LIGHT -----------------------------
   for(int k=0; k<numLights; k++) {
      Ray rayToLight = Ray(p,lights[k]->pos);
      double cosTheta = rayToLight.dir.dotProduct(normal);

      // negative means the angle is greater than 90
      if(cosTheta < 0) {
         totCol += HiDefColor(0,0,0); // black because the ray will NOT hit the position
      }
      else {
         // find the direction vector of the ray that perfectly reflects from the light to camera
         Vector3D reflection = activeCamera.getForward() - (normal * (2 * normal.dotProduct(activeCamera.getForward()) ));
         double cosPhi = rayToLight.dir.dotProduct(reflection);
         HiDefColor specColor = lights[k]->col * lights[k]->intensity;

         totCol += (diffuse * lights[k]->intensity) * cosTheta + ((specColor) * pow(cosPhi,shininess));
      }
   }
   sf::Color finalCol = sf::Color(totCol.r > 255 ? 255 : totCol.r,
                                  totCol.g > 255 ? 255 : totCol.g,
                                  totCol.b > 255 ? 255 : totCol.b);
   return finalCol;
}

GoochShader::GoochShader(sf::Color c, sf::Color cool, sf::Color warm, bool outline, const std::vector<Light*>& lights, const Camera& activeCamera)
   : Shader(lights,activeCamera), outline(outline)
{
   diffuse.r = c.r; diffuse.g = c.g; diffuse.b = c.b;
   HiDefColor cl(cool.r,cool.g,cool.b);
   HiDefColor wrm(warm.r,warm.g,warm.b);

   k_diffCool = cl + diffuse*0.2;
   k_diffWarm = wrm + diffuse*0.2;
}

sf::Color GoochShader::getColor(const Ray& r, const Vector3D& p, const Shape * sh) const {
   Vector3D normal = sh->getNormal(p).normalize();

   if(outline) {
      //------- Draw the outline (this is independent of lights) -------
      double cosPsi = r.dir.dotProduct(normal);
      // check if the angle between the normal and ray is within 5 degrees of 90
      if(cosPsi < 0.3 && cosPsi > -0.3) {
         return sf::Color(0,0,0); // black for the outline
      }
   }

   unsigned int numLights = lights.size();
   double shininess = 100;
   HiDefColor ambient(0,30,0);
   HiDefColor totCol(0,0,0);
   //-------------------- FOR EACH LIGHT -----------------------------
   for(int k=0; k<numLights; k++) {
      Ray rayToLight = Ray(p,lights[k]->pos);
      double cosTheta = rayToLight.dir.dotProduct(normal);

      // negative means the angle is greater than 90
      if(cosTheta < 0) {
         totCol += HiDefColor(0,0,0); // black because the ray will NOT hit the position
      }
      else {
         // find the direction vector of the ray that perfectly reflects from the light to camera
         Vector3D reflection = activeCamera.getForward() - (normal * (2 * normal.dotProduct(activeCamera.getForward()) ));
         double cosPhi = rayToLight.dir.dotProduct(reflection);
         cosPhi = cosPhi < 0.95 && cosPhi > -0.95 ? 0 : 1.0;
         HiDefColor specColor = lights[k]->col * lights[k]->intensity;
         double c = (cosTheta+1)/2.0;

         totCol += k_diffCool * c + k_diffWarm * (1.0 - c) + (specColor) * pow(cosPhi,shininess);
         //totCol += (ambient * (1.0 - c) * lights[k]->intensity) + (diffuse * c);
      }
   }
   sf::Color finalCol = sf::Color(totCol.r > 255 ? 255 : totCol.r,
                                  totCol.g > 255 ? 255 : totCol.g,
                                  totCol.b > 255 ? 255 : totCol.b);
   return finalCol;
}
