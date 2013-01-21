//-------------------------------------------------
//------------- SCENE.CPP -----------------------
//-------------------------------------------------
//#include "StdAfx.h"
#include <cstdio>
#include <include/Scene.h>

void Scene::render() {

		std::cout << "rendering\n";
		mainRayGun.start(sceneObjects);
		//mainRayGun.fire(sceneObjects);

		unsigned char* targaimage = new unsigned char[1280*720*3];
		for(int i=0; i<1280*720*3; i+=3) {
			targaimage[i] = mainRayGun.getColor(i/3).r;
			targaimage[i+1] = mainRayGun.getColor(i/3).g;
			targaimage[i+2] = mainRayGun.getColor(i/3).b;
			//targaimage[i+2] = mainRayGun.pix[i/3].color.b;
			//if(mainRayGun.pix[i/3].color.r == 255) std::cout << "white!" << std::endl;
		}

		if (!tga_write_raw("output.tga", 1280, 720, targaimage, TGA_TRUECOLOR_24)) {
			printf("Failed to write image!\n");
			printf(tga_error_string(tga_get_last_error()));
		}
		std::cout << "done\n";
		delete [] targaimage;
	}
