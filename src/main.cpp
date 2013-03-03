//-------------------------------------------------
//------------- MAIN.CPP ---------------------
//------------- MAIN ENTRY POINT ------------------
//-------------------------------------------------
//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <include/Application.h>
#include <QApplication>

int main(int argc, char* argv[])
{
   QApplication QApp(argc, argv);

   Application::create("assets/");
   Application *app = Application::getInstance();
   app->show();

   QApp.exec();

   return 0;
}

