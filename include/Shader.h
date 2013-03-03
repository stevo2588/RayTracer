#ifndef SHADER_H
#define SHADER_H

#include <SFML/Graphics.hpp>
#include <include/Utility.h>
#include <include/Camera.h>

class Light;
class Shape;


class Shader {
public:
   Shader(const std::vector<Light*>& lights, const Camera& activeCamera);
   virtual sf::Color getColor(const Ray& r, const Vector3D& p, const Shape * sh) const =0;

protected:
   const std::vector<Light*>& lights; // reference to scene lights
   const Camera& activeCamera; // reference to active scene camera
};

class PhongShader : public Shader {
public:
   PhongShader(sf::Color c, const std::vector<Light*>& lights, const Camera& activeCamera);
   sf::Color getColor(const Ray& r, const Vector3D& p, const Shape * sh) const;

private:
   HiDefColor diffuse;
};

class GoochShader : public Shader {
public:
   GoochShader(sf::Color c, sf::Color cool, sf::Color warm, bool outline, const std::vector<Light*>& lights, const Camera& activeCamera);
   sf::Color getColor(const Ray& r, const Vector3D& p, const Shape * sh) const;

private:
   HiDefColor diffuse;
   HiDefColor k_diffCool;
   HiDefColor k_diffWarm;
   bool outline;
};

#endif // SHADER_H
