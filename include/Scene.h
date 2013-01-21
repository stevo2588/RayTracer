//-------------------------------------------------
//------------- SCENE.H ---------------------------
//-------------------------------------------------
#pragma once
#ifndef RAYTRACER_SCENE_H_
#define RAYTRACER_SCENE_H_

#include <iostream> // remove me
#include "RayGun.h"
#include <vector>
#include "libtarga.h"

class Shape;

class Scene {
private:
	RayGun mainRayGun;
	std::vector<Shape*> sceneObjects;
	// add lights
public:
	Scene(RayGun& r, std::vector<Shape*>& s) : mainRayGun(r), sceneObjects(s) {}
	void render(); // currently a scene is limited to only 1 RayGun, so no need to specify which one to render from
};

#endif // RAYTRACER_SCENE_H_
