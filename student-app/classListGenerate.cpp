/*
 * classlistGenerate.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#include "classListGenerate.h"
#include <Wt/WBreak.h>

ClassListGenerateWidget::ClassListGenerateWidget() : Wt::WContainerWidget()
{
	addWidget(std::make_unique<Wt::WText>("Generate a class list for each section."));

	addWidget(std::make_unique<Wt::WBreak>());
	addWidget(std::make_unique<Wt::WBreak>());

	generateClassListButton = addWidget(std::make_unique<Wt::WPushButton>("Generate Class List"));
	addWidget(std::make_unique<Wt::WBreak>());

	queryResponse = addWidget(std::make_unique<Wt::WText>());

	generateClassListButton->clicked().connect(this, &ClassListGenerateWidget::generateClassList);
}

void ClassListGenerateWidget::generateClassList()
{
	std::string output_string;

	// run the SQL query and stuff it into string
	output_string = "Class List Query not implemented yet";

	queryResponse->setText(output_string);
}
