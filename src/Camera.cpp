//-------------------------------------------------
//------------- RAYGUN.CPP ------------------------
//-------------------------------------------------
//#include "stdafx.h"
#include <include/Camera.h>
#include <cmath>

Camera::Camera(Vector3D pos, Vector3D forward, Vector3D up) {
   this->pos = pos;
   this->forward = forward.normalize();
   this->up = up.normalize();
}
