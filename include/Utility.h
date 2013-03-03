//-------------------------------------------------
//------------- UTILITIES.H -----------------------
//-------------------------------------------------
#pragma once
#ifndef RAYTRACER_UTILITY_H_
#define RAYTRACER_UTILITY_H_

#include <iostream> // remove
#include <sstream>
#include <cstddef>
#include <vector>
class Shape;
class Matrix3D;

//------------- Vector3D ----------------------------
class Vector3D {
public:
	double elements[3];
public:
	Vector3D();
	Vector3D(double x, double y, double z);

   double calcMagnitude();
   Vector3D normalize();
	Vector3D& operator=(const Vector3D &rhs);
	Vector3D operator-() const;
	friend Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
	friend Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
	double dotProduct(const Vector3D &v) const;
	Vector3D crossProduct(const Vector3D &v);
	friend Vector3D operator*(const Vector3D &v1, const double s); // need the same with arguments switched?
	friend Vector3D operator/(const Vector3D &v1, const double s);
	friend Vector3D operator*(const Matrix3D &s, const Vector3D &v);
	friend Vector3D m_mult_dirVec(const Matrix3D &s, const Vector3D &v);

	std::string toString() const {
	   std::ostringstream convert;
	   convert << "(" << elements[0] << "," << elements[1] << "," << elements[2] << ")";
	   return convert.str();
   }
};

//------------- Matrix3D ----------------------------
class Matrix3D { // TODO: change to [3][4]
public:
	double elements[4][4];

public:
	Matrix3D();
	Matrix3D(double elem[4][4]);
	Matrix3D(double x, double y, double z);
	void setIDMat();
	void translate(double x, double y, double z);
	Vector3D getPos();
	double getElem(int row, int column) const { return elements[row][column]; }

	bool getInversion(Matrix3D &invOut); // return true if matrix is invertible, stores inverse in invOut
	Matrix3D& operator=(const Matrix3D &rhs);
	friend Matrix3D operator*(const Matrix3D &s1, const Matrix3D &s2);

	void printElements() const;
};

//------------- Ray -----------------------------
class Ray {
public:
	Vector3D src;
	Vector3D dir;

public:
	Ray(Vector3D const& src, Vector3D const& endPt);
	std::string toString() const {
	   std::ostringstream convert;
	   convert << "src: (" << src.elements[0] << "," << src.elements[1] << "," << src.elements[2] << "), "
	   << "dir: (" << dir.elements[0] << "," << dir.elements[1] << "," << dir.elements[2] << ")";
	   return convert.str();
   }
};

//------------- HiDefColor ----------------------------
class HiDefColor {
public:
	float r,g,b;
public:
	HiDefColor() : r(0), g(0), b(0) {}
	HiDefColor(float r,float g,float b) : r(r),g(g),b(b) {}
	HiDefColor(const HiDefColor& clr) : r(clr.r), g(clr.g), b(clr.b) {}
	HiDefColor& operator=(const HiDefColor &rhs);
	HiDefColor& operator+=(const HiDefColor &rhs);
	friend HiDefColor operator+(const HiDefColor &c1, const HiDefColor &c2);
	friend HiDefColor operator-(const HiDefColor &c1, const HiDefColor &c2);
	friend HiDefColor operator*(const HiDefColor &lhs, double rhs);
};

struct Hit {
   double distance;
};

#endif // RAYTRACER_UTILITY_H_
