/*
 * studentRegister.h
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#ifndef STUDENTREGISTER_H_
#define STUDENTREGISTER_H_

#include <memory>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "student-app.h"
#include <mysql/jdbc.h>

class StudentApplication;

class StudentRegisterWidget : public Wt::WContainerWidget
{
public:
	StudentRegisterWidget(StudentApplication *parent);
	int updateNumCourses();

private:
	StudentApplication* m_parent;

	sql::Driver *driver_ptr;
	std::unique_ptr<sql::Connection> con_ptr;

	const int course_limit = 5;

	// inputs to query
	Wt::WText *courseCodeText;
	Wt::WLineEdit *courseCodeEdit;
	Wt::WText *timeText;
	Wt::WLineEdit *timeEdit;
	Wt::WText *sectionNumberText;
	Wt::WLineEdit *sectionNumberEdit;

	// Query outputs
	Wt::WText *numCourses;
	Wt::WText *queryResponse;

	// Run Query
	Wt::WPushButton *registerCourseButton;

	// Slot
	void registerCourse();
	std::string handle_SQLException(sql::SQLException &e);
};




#endif /* STUDENTREGISTER_H_ */
