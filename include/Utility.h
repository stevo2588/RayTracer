//-------------------------------------------------
//------------- UTILITIES.H -----------------------
//-------------------------------------------------
#pragma once
#ifndef RAYTRACER_UTILITY_H_
#define RAYTRACER_UTILITY_H_

#include <iostream> // remove me
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
	Vector3D& operator=(const Vector3D &rhs);
	friend Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
	friend Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
	double dotProduct(const Vector3D &v);
	friend double operator *(const Vector3D &v1, const double s); // need the same with arguments switched?
	friend Vector3D operator*(const Matrix3D &s, const Vector3D &v);
	friend Vector3D m_mult_dirVec(const Matrix3D &s, const Vector3D &v);

	void printElements() const {for(int i=0; i<3; ++i) std::cout << elements[i] << " "; std::cout << std::endl;}
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
	Vector3D srcPos;
	Vector3D dirPos;
	
public:
	Ray(Vector3D const& src, Vector3D const& dir) : srcPos(src),dirPos(dir) {} // possible mem leak?
};

//------------- Color ----------------------------
class Color {
public:
	double r,g,b;
public:
	Color() : r(0), g(0), b(0) {}
	Color(double r,double g,double b) : r(r),g(g),b(b) {}
	Color(const Color& clr) : r(clr.r), g(clr.g), b(clr.b) {}
	Color& operator=(const Color &rhs);
	friend Color operator+(const Color &c1, const Color &c2);
	friend Color operator-(const Color &c1, const Color &c2);
};

#endif // RAYTRACER_UTILITY_H_