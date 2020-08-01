//============================================================================
// Name        : student-app.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================
#include <iostream>
#include <Wt/WServer.h>
#include "student-app.h"


using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	cout << "Running Student Application" << endl;
	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
      return std::make_unique<StudentApplication>(env);
    });
}
