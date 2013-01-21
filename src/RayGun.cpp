//-------------------------------------------------
//------------- RAYGUN.CPP ------------------------
//-------------------------------------------------
//#include "stdafx.h"
#include <include/RayGun.h>
#include <iostream> // remove me
#include <cmath>

RayGun::RayGun(Matrix3D space, double d, const renderParams& rp, Sampler* s) : pixGrid(rp.gridWidth,rp.gridHeight,rp.pixPerRow,rp.pixPerCol) {
	this->worldSpace = space;
	Matrix3D gm = this->worldSpace * Matrix3D(0,0,-d);
	this->pixGrid.setMatrix(gm);
	this->samp = s;
}

// recursively trace (world space) ray and detect intersections
void RayGun::rayTrace(const Ray& r, Color& c, const std::vector<Shape*> allObjects) {
	double* t = NULL; // TODO: will this cause memory leak???
	for(unsigned int i=0; i<allObjects.size(); ++i) { // do for all objects in scene
		if(allObjects[i]->intersection(r,t)) c = Color(255,255,255); //TODO: temporary, should use to calc. intersection point and return texture based on that
		else c = Color(0,0,0);
	}
	//std::cout << r.dirPos.elements[0] << "," << r.dirPos.elements[1] << "," << r.dirPos.elements[2] << std::endl;
}

void RayGun::fire(const std::vector<Shape*> allObjects) {
	int numEligPix = samp->toSample.size();
	for(unsigned int i=samp->toSample[0]; i<numEligPix; i=samp->toSample[i]) { // for every eligible pixel
		int numPoints = samp->rayPts[i].size();
		for(int j=0; j<numPoints; j++) {
			rayTrace(Ray(getMatrix().getPos(), samp->rayPts[i][j]), samp->colors[i][j], allObjects);
		}
	}
}

void RayGun::start(const std::vector<Shape*> allObjects) {
	bool sampleAgain = true;
	while(sampleAgain) {
		samp->rayAllocator(pixGrid);
		fire(allObjects);
		samp->processor(pixGrid);
		sampleAgain = samp->toSample.size() ? true : false; // sample again if there are eligible pixels
	}
}

Grid::Grid(Matrix3D m, double w, double h, int rl, int cl)
	: worldSpace(m),width(w),height(h),rowLength(rl),columnLength(cl),pix(rl*cl) {}

Grid::Grid(double w, double h, int rl, int cl)
	: worldSpace(),width(w),height(h),rowLength(rl),columnLength(cl),pix(rl*cl) {}

Sampler::Sampler(const renderParams& rp) : toSample(rp.pixPerRow*rp.pixPerCol), rayPts(), colors() {
		int numPix = toSample.size();
		for(int i=0; i<numPix; i++) { toSample[i] = i; }
}

void FixedInner::rayAllocator(const Grid& g) { // numRays must be an integer squared
	double pixWidth = g.getWidth()/g.getRowLength();
	double pixHeight = g.getHeight()/g.getColLength();
	int numPix = g.getSize();
	Vector3D gridTopLeft = Vector3D(-(0.5 * g.getWidth()),(0.5 * g.getHeight()),0);

	double theSqrt = sqrt((double)numRays);
	double offsetX = pixWidth/(theSqrt);
	double offsetY = pixHeight/(theSqrt);

	for(int i=0; i<numPix; i++) {
		for(int j=0; j<numRays; j++) {
			Vector3D v = g.getMatrix() * Vector3D(((j%(int)theSqrt)+1)*offsetX,((j/(int)theSqrt)+1)*offsetY,0);
			rayPts[i].push_back(v);
		}
	}

	//for(std::vector<Vector3D>::size_type i=0; i<pixelCenters.size(); ++i) {
	//	std::cout << pixelCenters[i].x << ' '
	//	          << pixelCenters[i].y << ' '
	//			  << pixelCenters[i].z << std::endl;
	//	std::cin.get();
	//}
}

void FixedInner::processor(Grid& g) {
	this->toSample.clear();

	// calculate average color per pixel
	for(int i=0; i<this->colors.size(); i++){
		Color avgClr = Color();
		int numClrs = this->colors[i].size();
		for(int j=0; j<this->colors[i].size(); j++){
			avgClr.r += this->colors[i][j].r;
			avgClr.g += this->colors[i][j].g;
			avgClr.b += this->colors[i][j].b;
		}
		avgClr.r = avgClr.r/numClrs;
		avgClr.g = avgClr.g/numClrs;
		avgClr.b = avgClr.b/numClrs;
		g.setColor(i, avgClr);
	}
}
