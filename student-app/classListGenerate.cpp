/*
 * classlistGenerate.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#include "classListGenerate.h"

ClassListGenerateWidget::ClassListGenerateWidget() : Wt::WContainerWidget()
{
	addWidget(std::make_unique<Wt::WText>("Generate a class list for each section."));
}
