//============================================================================
// Name        : student-app.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================
#include <iostream>
#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include "student-app.h"


using std::cout;
using std::endl;

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
  auto app = std::make_unique<Wt::WApplication>(env);

  app->setTitle("Student Application");
  app->useStyleSheet("student-app.css");
  app->root()->addWidget(std::make_unique<StudentApplication>());

  return app;
}

int main(int argc, char **argv)
{
	cout << "Running Student Application" << endl;

	try
	{
	    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
	    server.addEntryPoint(Wt::EntryPointType::Application, createApplication);
	    server.run();
	} catch (std::exception &e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}
}
