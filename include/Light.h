
//-------------------------------------------------
//------------- LIGHT.H --------------------------
//-------------------------------------------------
#pragma once
#ifndef LIGHT_H_
#define LIGHT_H_

#include <iostream> // remove me
#include <include/Utility.h>
#include <SFML/Graphics.hpp>

class Light {
public:
   Light(const Vector3D& pos, double intensity, bool shadows, std::string name, const sf::Color& col = sf::Color::White)
      : pos(pos), col(HiDefColor(col.r,col.g,col.b)), intensity(intensity), shadows(shadows), name(name) {}

	Vector3D pos;
	HiDefColor col;
	double intensity;
	bool shadows;
	std::string name;
};

class PointLight : public Light {
public:
	PointLight(const Vector3D& pos, double intensity, bool shadows, std::string name, const sf::Color& col = sf::Color::White) : Light(pos,intensity,shadows,name,col) {}
};

#endif // LIGHT_H_
