/*
 * studentRegister.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */
#include "studentRegister.h"

StudentRegisterWidget::StudentRegisterWidget(): Wt::WContainerWidget()
{
	addWidget(std::make_unique<Wt::WText>("Register student for a course"));
}
