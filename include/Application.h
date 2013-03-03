// Stephen Aldriedge

#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <QMainWindow>
#include <QtUiTools/QtUiTools>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <include/RenderParams.h>
#include <include/RayTracer.h>
#include <include/Scene.h>

class QSFMLCanvas;

//----------------------- APPLICATION ----------------------------------------

class Application : public QMainWindow {

   Q_OBJECT
private:
   Application(std::string assets);   // private constructor
public:
   static void create(std::string assets);
   static Application* getInstance(); // get a pointer to the instance
   ~Application() { instanceFlag = false; }
   friend class RayTracer;

protected:
    void closeEvent(QCloseEvent *event);
    void customEvent(QEvent *event);

private:
   static bool instanceFlag;    // tells us if an instance exists
   static Application *single;  // pointer to the application instance

   int getDir(std::string dir, std::vector<std::string> &files);
   bool fexists(std::string filename);
   void resizeMe(int width, int height);
   void display(int width, int height);

   RayTracer *raytracer;
   QSFMLCanvas* SFMLView;

   RenderParams rp;
   std::string saveFileName;
   std::string assets;

private slots:
   void raytrace();
   void setResolutionX(int width);
   void setResolutionY(int height);
   void setFocalLength(double length);
   void setLensWidth(double width);
   void setSubDiv(int subdiv);
   void setScene(QString filename);
   void browseScene();
   void setImageFile(QString filename);
   void saveImage();

};

#endif // APPLICATION_H
