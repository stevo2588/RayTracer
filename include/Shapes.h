//-------------------------------------------------
//------------- SHAPES.H --------------------------
//-------------------------------------------------
#pragma once
#ifndef RAYTRACER_SHAPES_H_
#define RAYTRACER_SHAPES_H_

#include <iostream> // remove me
#include "Utility.h"

// forward declarations go here

class Shape {
protected:
	Matrix3D worldSpace;
	Matrix3D inverse;

	Shape(const Vector3D& pos) : worldSpace(pos.elements[0],pos.elements[1],pos.elements[2]) {
		worldSpace.getInversion(inverse); // need to check if invertible?
	}

public:
	virtual bool intersection(const Ray& r, double* t) const =0; // returns distance of the ray when it hits shape
};

class Sphere : public Shape {
private:
	double radius;
	Color tex;

public:
	Sphere(const double r, const Vector3D& pos, const Color& c) : Shape(pos), radius(r), tex(c) {}
	bool intersection(const Ray& r, double* t) const;
};

#endif // RAYTRACER_SHAPES_H_