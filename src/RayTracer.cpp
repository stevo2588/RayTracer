//-------------------------------------------------
//------------- RAYTRACER.CPP ---------------------
//------------- MAIN ENTRY POINT ------------------
//-------------------------------------------------
//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <include/Utility.h>
#include <include/Shapes.h>
#include <include/RayGun.h>
#include <include/Scene.h>

int main(int argc, char* argv[])
{
	renderParams rp;
	rp.gridWidth = .05333;
	rp.gridHeight = .03;
	rp.pixPerRow = 1280;
	rp.pixPerCol = 720;
	rp.sampling = renderParams::FixedInner;
	rp.numRays = 1;

	FixedInner FISampler(rp);
	Sampler * samp = &FISampler;

	Matrix3D raySpace(0,0,10);
	RayGun rg = RayGun(raySpace,5.0,rp,samp);

	std::vector<Shape*> sceneObjects;
	Sphere sp(15.0,Vector3D(40.0,0,-6),Color(255,255,255));
	Shape * shp = &sp;
	sceneObjects.push_back(shp);

	Scene mainScene(rg, sceneObjects);
	mainScene.render();


	/*
	// Matrix * Vector Testing
	Matrix3D m(3,4,5);
	Vector3D v(2,3,4);
	Vector3D p = m*v;
	p.printElements();
	*/

	/*
	// intersection testing
	Sphere sp(10.0,Vector3D(0,0,-8),Color(255,255,255));
	Ray r1(Vector3D(0,0,10),Vector3D(0,50,-20));
	sp.intersection(r1);
	*/

	std::cout << "Press Enter to continue";
	std::cin.get();

	return 0;
}

