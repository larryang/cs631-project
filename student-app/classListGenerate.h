/*
 * classlistGenerate.h
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#ifndef CLASSLISTGENERATE_H_
#define CLASSLISTGENERATE_H_

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class ClassListGenerateWidget : public Wt::WContainerWidget
{
public:
	ClassListGenerateWidget();

private:
	Wt::WPushButton *generateClassListButton;
	Wt::WText *queryResponse;

	// SLOTS
	void generateClassList(); // probably could just do all of this in the constructor
};



#endif /* CLASSLISTGENERATE_H_ */
