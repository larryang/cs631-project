/*
 * studentRegister.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */
#include "studentRegister.h"
#include "Wt/WBreak.h"
//#include "connectMySql.h"

StudentRegisterWidget::StudentRegisterWidget(StudentApplication* parent) : Wt::WContainerWidget()
{
	m_parent = parent;

	addWidget(std::make_unique<Wt::WText>("Register student for a course"));

	addWidget(std::make_unique<Wt::WBreak>());
	addWidget(std::make_unique<Wt::WBreak>());

	courseCodeText = addWidget(std::make_unique<Wt::WText>("Course Code "));
	courseCodeEdit = addWidget(std::make_unique<Wt::WLineEdit>());
	addWidget(std::make_unique<Wt::WBreak>());
	timeText = addWidget(std::make_unique<Wt::WText>("Time"));
	timeEdit = addWidget(std::make_unique<Wt::WLineEdit>());
	addWidget(std::make_unique<Wt::WBreak>());
	sectionNumberText = addWidget(std::make_unique<Wt::WText>("Section Number"));
	sectionNumberEdit = addWidget(std::make_unique<Wt::WLineEdit>());
	addWidget(std::make_unique<Wt::WBreak>());
	registerCourseButton = addWidget(std::make_unique<Wt::WPushButton>("Register"));
	addWidget(std::make_unique<Wt::WBreak>());

	queryResponse = addWidget(std::make_unique<Wt::WText>());

	registerCourseButton->clicked().connect(this, &StudentRegisterWidget::registerCourse);
}


void StudentRegisterWidget::registerCourse()
{
	// get query input
	std::string studentId = m_parent->studentId();
	std::string courseCode = courseCodeEdit->text().toUTF8();
	std::string time = timeEdit->text().toUTF8();
	std::string sectionNumber = sectionNumberEdit->text().toUTF8();

	// declare query output
	std::string output_text;

	// do MySQL query - put output into this output_text string
	output_text = "Query not implemented yet. StudentID: " + m_parent->studentId()
			+ " CourseCode: " + courseCode + " Time: " + time + " SectionNumber: " + sectionNumber;

	queryResponse->setText(output_text);
}
