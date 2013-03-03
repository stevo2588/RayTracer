//-------------------------------------------------
//------------- SCENE.H ---------------------------
//-------------------------------------------------
#pragma once
#ifndef RAYTRACER_SCENE_H_
#define RAYTRACER_SCENE_H_

#include <vector>
#include <include/Camera.h>
#include <include/Light.h>

class Shape;

class Scene {
public:
   Scene(); // default creates the example scene
	Scene(Camera& r, std::vector<Shape*>& s, std::vector<Light*>& l) : mainCamera(r), sceneObjects(s), sceneLights(l) {}
	Camera mainCamera;
	std::vector<Shape*> sceneObjects;
	std::vector<Light*> sceneLights;
};

#endif // RAYTRACER_SCENE_H_
