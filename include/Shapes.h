//-------------------------------------------------
//------------- SHAPES.H --------------------------
//-------------------------------------------------
#pragma once
#ifndef RAYTRACER_SHAPES_H_
#define RAYTRACER_SHAPES_H_

#include <iostream> // remove me
#include <include/Utility.h>
#include <include/Shader.h>

class Shape {
protected:
	Vector3D pos;
	const Shader *sh;
	std::string name;

	Shape(const Vector3D& pos, const Shader* sh, std::string name) : pos(pos), sh(sh), name(name) {
	}

public:
	virtual bool intersection(const Ray& r, Hit* h) const =0;
	const Shader* getShader() const {return sh;}
	Vector3D getPos() const {return pos;}
	std::string getName() const {return name;}
	virtual Vector3D getNormal(const Vector3D& p) const =0;
};

class Sphere : public Shape {
private:
	double radius;

public:
	Sphere(const double r, const Vector3D& pos, const Shader* sh, std::string name) : Shape(pos,sh,name), radius(r) {}
	bool intersection(const Ray& r, Hit* h) const;
	Vector3D getNormal(const Vector3D& p) const;
};

class Plane : public Shape {
private:
	double radius;
	Vector3D normal;

public:
	Plane(const Vector3D& norm, const Vector3D& pos, const Shader* sh, std::string name) : Shape(pos,sh,name), normal(norm) {}
	bool intersection(const Ray& r, Hit* h) const;
	Vector3D getNormal(const Vector3D& p) const {return normal;}
};

#endif // RAYTRACER_SHAPES_H_
