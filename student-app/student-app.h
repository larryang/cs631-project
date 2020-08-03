/*
 * student-app.h
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#ifndef STUDENT_APP_H_
#define STUDENT_APP_H_

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include "studentRegister.h"
#include "classListGenerate.h"

using std::string;

class StudentRegisterWidget;
class ClassListGenerateWidget;

class StudentApplication : public Wt::WContainerWidget
{
public:
	StudentApplication();
	std::string studentId();

private:
	// Variables
	bool m_isLoggedIn = 0;
	Wt::WString m_userId;
	Wt::WString m_password;

	// SQL stuff
	sql::Driver *driver_ptr;
	std::unique_ptr<sql::Connection> con_ptr;

	Wt::WText *greeting_;

	Wt::WText *userIdText;
	Wt::WLineEdit *userIdEdit;
	Wt::WText *passwordText;
	Wt::WLineEdit *passwordEdit;

	Wt::WPushButton *loginButton;
	Wt::WPushButton *logoutButton;

	StudentRegisterWidget *registerWidget;
	Wt::WPushButton *registerButton;

	ClassListGenerateWidget *generateClassListWidget;
	Wt::WPushButton *generateClassListButton;

	Wt::WPushButton *doneButton;

	// Slots
	void login();
	void logout();
	void registerStudent();
	void generateClassList();
	void done();

	// methods
	std::string handle_SQLException(sql::SQLException &e);
	bool checkStudentUserId(std::string userId);
};

#endif /* STUDENT_APP_H_ */
