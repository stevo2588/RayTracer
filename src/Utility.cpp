//-------------------------------------------------
//------------- UTILITY.CPP -----------------------
//-------------------------------------------------
//#include "stdafx.h"
#include <iostream>
#include <include/Utility.h>

//------------- Vector3D ----------------------------
Vector3D::Vector3D() {
	elements[0] = 0;
	elements[1] = 0;
	elements[2] = 0;
}

Vector3D::Vector3D(double x, double y, double z) {
	elements[0] = x;
	elements[1] = y;
	elements[2] = z;
}

double Vector3D::dotProduct(const Vector3D &v) {
	double prod = this->elements[0]*v.elements[0] + this->elements[1]*v.elements[1] + this->elements[2]*v.elements[2];
	return prod;
}

Vector3D& Vector3D::operator=(const Vector3D &rhs) {
	if(this != &rhs) {
		// Deallocate, allocate new space, copy values
		this->elements[0] = rhs.elements[0];
		this->elements[1] = rhs.elements[1];
		this->elements[2] = rhs.elements[2];
	}
	return *this;
}

Vector3D operator+(const Vector3D &v1, const Vector3D &v2) {
	return Vector3D(v1.elements[0]+v2.elements[0], v1.elements[1]+v2.elements[1], v1.elements[2]+v2.elements[2]);
}

Vector3D operator-(const Vector3D &v1, const Vector3D &v2) {
	return Vector3D(v1.elements[0]-v2.elements[0], v1.elements[1]-v2.elements[1], v1.elements[2]-v2.elements[2]);
}

double operator*(const Vector3D &v1, const Vector3D &v2) {
	return (v1.elements[0]*v2.elements[0]) + (v1.elements[1]*v2.elements[1]) + (v1.elements[2]*v2.elements[2]);
}

Vector3D operator*(const Matrix3D &s, const Vector3D &v) { // technically post-multiplication
	Vector3D prod(0,0,0);

	prod.elements[0] = s.elements[0][0]*v.elements[0] + s.elements[0][1]*v.elements[1] + s.elements[0][2]*v.elements[2] + s.elements[0][3];
	prod.elements[1] = s.elements[1][0]*v.elements[0] + s.elements[1][1]*v.elements[1] + s.elements[1][2]*v.elements[2] + s.elements[1][3];
	prod.elements[2] = s.elements[2][0]*v.elements[0] + s.elements[2][1]*v.elements[1] + s.elements[2][2]*v.elements[2] + s.elements[2][3];

	return prod;
}

Vector3D m_mult_dirVec(const Matrix3D &s, const Vector3D &v) { // no translation, for use with direction vectors
	Vector3D prod(0,0,0);

	prod.elements[0] = s.elements[0][0]*v.elements[0] + s.elements[0][1]*v.elements[1] + s.elements[0][2]*v.elements[2];
	prod.elements[1] = s.elements[1][0]*v.elements[0] + s.elements[1][1]*v.elements[1] + s.elements[1][2]*v.elements[2];
	prod.elements[2] = s.elements[2][0]*v.elements[0] + s.elements[2][1]*v.elements[1] + s.elements[2][2]*v.elements[2];

	return prod;
}

//------------- Matrix3D ----------------------------
Matrix3D::Matrix3D() {
	setIDMat();
}

Matrix3D::Matrix3D(double elem[4][4]) {
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			elements[i][j] = elem[i][j];
}

Matrix3D::Matrix3D(double x, double y, double z) {
	elements[0][0] = 1; elements[0][1] = 0; elements[0][2] = 0; elements[0][3] = x;
	elements[1][0] = 0; elements[1][1] = 1; elements[1][2] = 0; elements[1][3] = y;
	elements[2][0] = 0; elements[2][1] = 0; elements[2][2] = 1; elements[2][3] = z;
	elements[3][0] = 0; elements[3][1] = 0; elements[3][2] = 0; elements[3][3] = 1;
}

void Matrix3D::setIDMat() {
	elements[0][0] = 1; elements[0][1] = 0; elements[0][2] = 0; elements[0][3] = 0;
	elements[1][0] = 0; elements[1][1] = 1; elements[1][2] = 0; elements[1][3] = 0;
	elements[2][0] = 0; elements[2][1] = 0; elements[2][2] = 1; elements[2][3] = 0;
	elements[3][0] = 0; elements[3][1] = 0; elements[3][2] = 0; elements[3][3] = 1;
}

void Matrix3D::translate(double x, double y, double z) {
	double transArr[4][4] = {{1,0,0,x},{0,1,0,y},{0,0,1,z},{0,0,0,1}};
	// TODO!
}

Vector3D Matrix3D::getPos() {
	return Vector3D(elements[0][3],elements[1][3],elements[2][3]);
}

bool Matrix3D::getInversion(Matrix3D &invOut) {
	Matrix3D inv;
	double det;
    //double inv[16], det;

    inv.elements[0][0] = elements[1][1]  * elements[2][2] * elements[3][3] -
             elements[1][1]  * elements[2][3] * elements[3][2] -
             elements[2][1]  * elements[1][2]  * elements[3][3] +
             elements[2][1]  * elements[1][3]  * elements[3][2] +
             elements[3][1] * elements[1][2]  * elements[2][3] -
             elements[3][1] * elements[1][3]  * elements[2][2];

    inv.elements[1][0] = -elements[1][0]  * elements[2][2] * elements[3][3] +
              elements[1][0]  * elements[2][3] * elements[3][2] +
              elements[2][0]  * elements[1][2]  * elements[3][3] -
              elements[2][0]  * elements[1][3]  * elements[3][2] -
              elements[3][0] * elements[1][2]  * elements[2][3] +
              elements[3][0] * elements[1][3]  * elements[2][2];

    inv.elements[2][0] = elements[1][0]  * elements[2][1] * elements[3][3] -
             elements[1][0]  * elements[2][3] * elements[3][1] -
             elements[2][0]  * elements[1][1] * elements[3][3] +
             elements[2][0]  * elements[1][3] * elements[3][1] +
             elements[3][0] * elements[1][1] * elements[2][3] -
             elements[3][0] * elements[1][3] * elements[2][1];

    inv.elements[3][0] = -elements[1][0]  * elements[2][1] * elements[3][2] +
               elements[1][0]  * elements[2][2] * elements[3][1] +
               elements[2][0]  * elements[1][1] * elements[3][2] -
               elements[2][0]  * elements[1][2] * elements[3][1] -
               elements[3][0] * elements[1][1] * elements[2][2] +
               elements[3][0] * elements[1][2] * elements[2][1];

    inv.elements[0][1] = -elements[0][1]  * elements[2][2] * elements[3][3] +
              elements[0][1]  * elements[2][3] * elements[3][2] +
              elements[2][1]  * elements[0][2] * elements[3][3] -
              elements[2][1]  * elements[0][3] * elements[3][2] -
              elements[3][1] * elements[0][2] * elements[2][3] +
              elements[3][1] * elements[0][3] * elements[2][2];

    inv.elements[1][1] = elements[0][0]  * elements[2][2] * elements[3][3] -
             elements[0][0]  * elements[2][3] * elements[3][2] -
             elements[2][0]  * elements[0][2] * elements[3][3] +
             elements[2][0]  * elements[0][3] * elements[3][2] +
             elements[3][0] * elements[0][2] * elements[2][3] -
             elements[3][0] * elements[0][3] * elements[2][2];

    inv.elements[2][1] = -elements[0][0]  * elements[2][1] * elements[3][3] +
              elements[0][0]  * elements[2][3] * elements[3][1] +
              elements[2][0]  * elements[0][1] * elements[3][3] -
              elements[2][0]  * elements[0][3] * elements[3][1] -
              elements[3][0] * elements[0][1] * elements[2][3] +
              elements[3][0] * elements[0][3] * elements[2][1];

    inv.elements[3][1] = elements[0][0]  * elements[2][1] * elements[3][2] -
              elements[0][0]  * elements[2][2] * elements[3][1] -
              elements[2][0]  * elements[0][1] * elements[3][2] +
              elements[2][0]  * elements[0][2] * elements[3][1] +
              elements[3][0] * elements[0][1] * elements[2][2] -
              elements[3][0] * elements[0][2] * elements[2][1];

    inv.elements[0][2] = elements[0][1]  * elements[1][2] * elements[3][3] -
             elements[0][1]  * elements[1][3] * elements[3][2] -
             elements[1][1]  * elements[0][2] * elements[3][3] +
             elements[1][1]  * elements[0][3] * elements[3][2] +
             elements[3][1] * elements[0][2] * elements[1][3] -
             elements[3][1] * elements[0][3] * elements[1][2];

    inv.elements[1][2] = -elements[0][0]  * elements[1][2] * elements[3][3] +
              elements[0][0]  * elements[1][3] * elements[3][2] +
              elements[1][0]  * elements[0][2] * elements[3][3] -
              elements[1][0]  * elements[0][3] * elements[3][2] -
              elements[3][0] * elements[0][2] * elements[1][3] +
              elements[3][0] * elements[0][3] * elements[1][2];

    inv.elements[2][2] = elements[0][0]  * elements[1][1] * elements[3][3] -
              elements[0][0]  * elements[1][3] * elements[3][1] -
              elements[1][0]  * elements[0][1] * elements[3][3] +
              elements[1][0]  * elements[0][3] * elements[3][1] +
              elements[3][0] * elements[0][1] * elements[1][3] -
              elements[3][0] * elements[0][3] * elements[1][1];

    inv.elements[3][2] = -elements[0][0]  * elements[1][1] * elements[3][2] +
               elements[0][0]  * elements[1][2] * elements[3][1] +
               elements[1][0]  * elements[0][1] * elements[3][2] -
               elements[1][0]  * elements[0][2] * elements[3][1] -
               elements[3][0] * elements[0][1] * elements[1][2] +
               elements[3][0] * elements[0][2] * elements[1][1];

    inv.elements[0][3] = -elements[0][1] * elements[1][2] * elements[2][3] +
              elements[0][1] * elements[1][3] * elements[2][2] +
              elements[1][1] * elements[0][2] * elements[2][3] -
              elements[1][1] * elements[0][3] * elements[2][2] -
              elements[2][1] * elements[0][2] * elements[1][3] +
              elements[2][1] * elements[0][3] * elements[1][2];

    inv.elements[1][3] = elements[0][0] * elements[1][2] * elements[2][3] -
             elements[0][0] * elements[1][3] * elements[2][2] -
             elements[1][0] * elements[0][2] * elements[2][3] +
             elements[1][0] * elements[0][3] * elements[2][2] +
             elements[2][0] * elements[0][2] * elements[1][3] -
             elements[2][0] * elements[0][3] * elements[1][2];

    inv.elements[2][3] = -elements[0][0] * elements[1][1] * elements[2][3] +
               elements[0][0] * elements[1][3] * elements[2][1] +
               elements[1][0] * elements[0][1] * elements[2][3] -
               elements[1][0] * elements[0][3] * elements[2][1] -
               elements[2][0] * elements[0][1] * elements[1][3] +
               elements[2][0] * elements[0][3] * elements[1][1];

    inv.elements[3][3] = elements[0][0] * elements[1][1] * elements[2][2] -
              elements[0][0] * elements[1][2] * elements[2][1] -
              elements[1][0] * elements[0][1] * elements[2][2] +
              elements[1][0] * elements[0][2] * elements[2][1] +
              elements[2][0] * elements[0][1] * elements[1][2] -
              elements[2][0] * elements[0][2] * elements[1][1];

    det = elements[0][0] * inv.elements[0][0] + elements[0][1] * inv.elements[1][0] + elements[0][2] * inv.elements[2][0] + elements[0][3] * inv.elements[3][0];

    if (det == 0) return false;

    det = 1.0 / det;

    for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			invOut.elements[i][j] = inv.elements[i][j] * det;

    return true;
}

Matrix3D& Matrix3D::operator=(const Matrix3D &rhs) {
	if(this != &rhs) {
		// Deallocate, allocate new space, copy values
		for(int i=0; i<4; ++i)
			for(int j=0; j<4; ++j)
				elements[i][j] = rhs.getElem(i,j);
	}
	return *this;
}

Matrix3D operator*(const Matrix3D &s1, const Matrix3D &s2) {
	Matrix3D prod;
	for(int k=0; k<4; ++k) {
		for(int i=0; i<4; ++i) {
			for(int j=0; j<4; ++j)
				prod.elements[k][i] += s1.elements[j][i] * s2.elements[k][j];
		}
	}
	return prod;
}

void Matrix3D::printElements() const {
	for(int i=0; i<4; ++i)
			std::cout << elements[i][0] << elements[i][1] << elements[i][2] << elements[i][3] << std::endl;
}

//------------- Ray ------------------------------


//------------- Color ----------------------------
Color& Color::operator=(const Color &rhs) {
	if(this != &rhs) {
		// Deallocate, allocate new space, copy values
		this->r = rhs.r;
		this->g = rhs.g;
		this->b = rhs.b;
	}
	return *this;
}
