#include <include/Scene.h>
#include <include/Utility.h>
#include <include/Shapes.h>
#include <include/Camera.h>
#include <include/Shader.h>

Scene::Scene()
   : mainCamera(Camera(Vector3D(0,0,20), Vector3D(0,0,-1), Vector3D(0,1,0)))
{
   PointLight * lt1 = new PointLight(Vector3D(-8,6,-4),0.8,true,"light01");
   PointLight * lt2 = new PointLight(Vector3D(4,-2,-3),0.6,true,"light02");
   sceneLights.push_back(lt1);
   sceneLights.push_back(lt2);

   PhongShader* simpleShader01 = new PhongShader(sf::Color::Blue,sceneLights,mainCamera);
   PhongShader* simpleShader02 = new PhongShader(sf::Color::Red,sceneLights,mainCamera);
   PhongShader* simpleShader03 = new PhongShader(sf::Color::Green,sceneLights,mainCamera);
   PhongShader* simpleShader04 = new PhongShader(sf::Color::White,sceneLights,mainCamera);
   PhongShader* simpleShader05 = new PhongShader(sf::Color(100,30,40),sceneLights,mainCamera);
   PhongShader* simpleShader06 = new PhongShader(sf::Color(20,200,200),sceneLights,mainCamera);
   /*GoochShader* goochShader01 = new GoochShader(sf::Color::Red,sf::Color(0,0,200),sf::Color(255,20,0), true ,sceneLights,mainCamera);
   GoochShader* goochShader02 = new GoochShader(sf::Color::Red,sf::Color(0,150,60),sf::Color(255,127,0), true, sceneLights,mainCamera);
   GoochShader* goochShader03 = new GoochShader(sf::Color::Green,sf::Color(0,0,200),sf::Color(255,20,0), false, sceneLights,mainCamera);
   GoochShader* goochShader04 = new GoochShader(sf::Color::Blue,sf::Color(0,150,60),sf::Color(255,127,0), false, sceneLights,mainCamera);
   GoochShader* goochShader05 = new GoochShader(sf::Color::Red,sf::Color(0,0,0),sf::Color(0,0,0), false ,sceneLights,mainCamera);
   GoochShader* goochShader06 = new GoochShader(sf::Color::Red,sf::Color(0,0,255),sf::Color(255,255,0), false ,sceneLights,mainCamera);

   Sphere * sp = new Sphere(4.0,Vector3D(-3,2,-23),goochShader02,"sphere01"); // TODO: this needs to get deleted somewhere/sometime
   Sphere * sp2 = new Sphere(6.0,Vector3D(2,-4,-22),goochShader01,"sphere02");
   Plane * pla1 = new Plane(Vector3D(0,1,0),Vector3D(0,-8,0),goochShader06,"plane01");
   Plane * pla2 = new Plane(Vector3D(-1,0,0),Vector3D(12,0,0),goochShader03,"plane02");
   Plane * pla3 = new Plane(Vector3D(0,-1,0),Vector3D(0,8,0),goochShader06,"plane03");
   Plane * pla4 = new Plane(Vector3D(1,0,0),Vector3D(-12,0,0),goochShader04,"plane04");
   Plane * pla5 = new Plane(Vector3D(0,0,1),Vector3D(0,0,-28),goochShader05,"plane05");*/
   Sphere * sp = new Sphere(4.0,Vector3D(-3,2,-23),simpleShader02,"sphere01"); // TODO: this needs to get deleted somewhere/sometime
   Sphere * sp2 = new Sphere(6.0,Vector3D(2,-4,-22),simpleShader01,"sphere02");
   Plane * pla1 = new Plane(Vector3D(0,1,0),Vector3D(0,-8,0),simpleShader06,"plane01");
   Plane * pla2 = new Plane(Vector3D(-1,0,0),Vector3D(12,0,0),simpleShader03,"plane02");
   Plane * pla3 = new Plane(Vector3D(0,-1,0),Vector3D(0,8,0),simpleShader06,"plane03");
   Plane * pla4 = new Plane(Vector3D(1,0,0),Vector3D(-12,0,0),simpleShader04,"plane04");
   Plane * pla5 = new Plane(Vector3D(0,0,1),Vector3D(0,0,-28),simpleShader05,"plane05");

   sceneObjects.push_back(sp);
   sceneObjects.push_back(sp2);
   sceneObjects.push_back(pla1);
   sceneObjects.push_back(pla2);
   sceneObjects.push_back(pla3);
   sceneObjects.push_back(pla4);
   sceneObjects.push_back(pla5);
}
