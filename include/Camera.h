//-------------------------------------------------
//------------- RAYGUN.H --------------------------
//-------------------------------------------------
#pragma once
#ifndef RAYTRACER_RAYGUN_H_
#define RAYTRACER_RAYGUN_H_

#include <include/Utility.h>

class Camera {
public:
	Camera(Vector3D pos, Vector3D forward, Vector3D up);
   Vector3D getPos() const {return pos;}
   Vector3D getForward() const {return forward;}
   Vector3D getUp() const {return up;}

private:
	Vector3D pos;
	Vector3D forward;
	Vector3D up;
};

#endif // RAYTRACER_RAYGUN_H_
