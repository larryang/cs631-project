/*
 * studentRegister.h
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#ifndef STUDENTREGISTER_H_
#define STUDENTREGISTER_H_

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class StudentRegisterWidget : public Wt::WContainerWidget
{
public:
	StudentRegisterWidget();

private:

	// inputs to query
	Wt::WText *courseCodeText;
	Wt::WLineEdit *courseCodeEdit;
	Wt::WText *timeText;
	Wt::WLineEdit *timeEdit;
	Wt::WText *sectionNumberText;
	Wt::WLineEdit *sectionNumberEdit;

	Wt::WText *queryResponse;

	// Run Query
	Wt::WPushButton *registerCourseButton;

	// Slot
	void registerCourse();
};




#endif /* STUDENTREGISTER_H_ */
