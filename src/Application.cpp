
#include <include/Application.h>

#include <include/Utility.h>
#include <include/Shapes.h>
#include <include/Camera.h>
#include <include/Scene.h>
#include <include/GUI/QSFMLCanvas.hpp>
#include <QApplication>
#include <QPushButton>
#include <QDockWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QString>
#include <iostream>
#include <string>
#include <sstream>
#include <GL/gl.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include <include/RayTracer.h>
#include <include/Events.h>

bool Application::instanceFlag = false;

Application* Application::single = NULL;

Application::Application(std::string assets) : assets(assets)
{
   QUiLoader loader;
   QFile file("Raytracer.ui");
   file.open(QFile::ReadOnly);
   QDockWidget* dockWidget = (QDockWidget*)loader.load(&file);
   file.close();
   addDockWidget(Qt::BottomDockWidgetArea, dockWidget);

   saveFileName = "";

   // ---------------- Set Default Render Parameters --------------------------------------------
   rp.setScene("");
   rp.setResolutionX(600);
   rp.setResolutionY(340);
   rp.setLensWidth(7);
   rp.setFocalLength(7);
   rp.setSubDiv(0);
   rp.setTraceDepth(1);

   //---------------- Set Initial State, then Connect signals and slots ----------------------------------------
   QPushButton* rayTraceButton = dockWidget->findChild<QPushButton*>("raytraceButton");
   connect(rayTraceButton, SIGNAL(clicked()), this, SLOT(raytrace()));
   QSpinBox* resolutionXSpinner = dockWidget->findChild<QSpinBox*>("resolutionXSpinner");
   resolutionXSpinner->setValue(rp.getResolutionX());
   connect(resolutionXSpinner, SIGNAL(valueChanged(int)), this, SLOT(setResolutionX(int)));
   QSpinBox* resolutionYSpinner = dockWidget->findChild<QSpinBox*>("resolutionYSpinner");
   resolutionYSpinner->setValue(rp.getResolutionY());
   connect(resolutionYSpinner, SIGNAL(valueChanged(int)), this, SLOT(setResolutionY(int)));
   QDoubleSpinBox* focalLengthSpinner = dockWidget->findChild<QDoubleSpinBox*>("focalLengthSpinner");
   focalLengthSpinner->setValue(rp.getFocalLength());
   connect(focalLengthSpinner, SIGNAL(valueChanged(double)), this, SLOT(setFocalLength(double)));
   QDoubleSpinBox* lensWidthSpinner = dockWidget->findChild<QDoubleSpinBox*>("lensWidthSpinner");
   lensWidthSpinner->setValue(rp.getLensWidth());
   connect(lensWidthSpinner, SIGNAL(valueChanged(double)), this, SLOT(setLensWidth(double)));
   QSpinBox* subDivSpinner = dockWidget->findChild<QSpinBox*>("subDivSpinner");
   subDivSpinner->setValue(rp.getSubDiv());
   connect(subDivSpinner, SIGNAL(valueChanged(int)), this, SLOT(setSubDiv(int)));
   QLineEdit* sceneFileBox = dockWidget->findChild<QLineEdit*>("sceneFileBox");
   QString qs = rp.getSceneName().c_str();
   sceneFileBox->insert(qs);
   connect(sceneFileBox, SIGNAL(textChanged(QString)), this, SLOT(setScene(QString)));
   QPushButton* sceneBrowseButton = dockWidget->findChild<QPushButton*>("sceneBrowseButton");
   connect(sceneBrowseButton, SIGNAL(clicked()), this, SLOT(browseScene()));
   QLineEdit* imageSaveBox = dockWidget->findChild<QLineEdit*>("imageSaveBox");
   connect(imageSaveBox, SIGNAL(textChanged(QString)), this, SLOT(setImageFile(QString)));
   QPushButton* saveButton = dockWidget->findChild<QPushButton*>("saveButton");
   connect(saveButton, SIGNAL(clicked()), this, SLOT(saveImage()));
   //--------------------------------------------------------------------------------------------------

   raytracer = new RayTracer(rp);

   // Create a SFML view
   SFMLView = new QSFMLCanvas(this, QPoint(20, 20), QSize(360, 360), raytracer->getImage());
   setCentralWidget(SFMLView);

   setWindowTitle("Raytracer");
   resize(900, 800);
}

void Application::create(std::string assets) {
   if(instanceFlag) return;   // if an instance already exists, do nothing
   else {                     // if instance doesn't exists, create it
      single = new Application(assets);
      instanceFlag = true;
   }
}

Application* Application::getInstance() {
    if(!instanceFlag) return NULL; // return NULL if no instance exists
    else return single;             // return existing instance
}

int Application::getDir(std::string dir, std::vector<std::string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
       std::string filename = dirp->d_name;
       if(filename != "." && filename != "..")
        files.push_back(std::string(filename));
    }
    closedir(dp);
    return 0;
}

// checks if a filename exists
bool Application::fexists(std::string filename) {
   std::ifstream ifile(filename.c_str());
   return ifile;
}

void Application::closeEvent(QCloseEvent *event) {

}

void Application::raytrace() {
   std::cout << "Ray tracing!" << std::endl;
   raytracer->init();   // certain initializations that are necessary to do in the main thread
   SFMLView->resizeSprite(); // let the SFML canvas know the image has changed
   raytracer->start();  // ray trace in a separate thread
   std::cout << "Doing my own thing now" << std::endl;
}

void Application::setResolutionX(int width) {
   rp.setResolutionX(width);
}
void Application::setResolutionY(int height) {
   rp.setResolutionY(height);
}
void Application::setFocalLength(double length){
   rp.setFocalLength(length);
}
void Application::setLensWidth(double width){
   rp.setLensWidth(width);
}
void Application::setSubDiv(int subdiv){
   rp.setSubDiv(subdiv);
}
void Application::setScene(QString filename) {
   rp.setScene(filename.toStdString());
}
void Application::browseScene() {
   // TODO
}
void Application::setImageFile(QString filename) {
   saveFileName = filename.toStdString();
}
void Application::saveImage() {
   SFMLView->getImageCopy().saveToFile(saveFileName);
}

void Application::customEvent(QEvent *event) {
   if (event->type() == RayTraceEvent::traceStart) {
      //std::cout << "traceStart" << std::endl;
   }
   else if (event->type() == RayTraceEvent::traceEnd) {
      //std::cout << "traceEnd" << std::endl;
   }
/*   else if (event->type() == RayTraceEvent::tracePixelFilled) {
      QApplication::postEvent(SFMLView, new QEvent(QEvent::Paint));
      //std::cout << "tracePixelFilled" << std::endl;
   }
*/
   else {
      QMainWindow::customEvent(event);
   }
}

