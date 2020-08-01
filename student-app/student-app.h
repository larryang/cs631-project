/*
 * student-app.h
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#ifndef STUDENT_APP_H_
#define STUDENT_APP_H_


#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "studentRegister.h"
#include "classListGenerate.h"

using std::string;

class StudentApplication : public Wt::WContainerWidget
{
public:
	StudentApplication();

private:
	// Variables
	bool m_isLoggedIn = 0;
	Wt::WString m_userId;
	Wt::WString m_password;

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

	// Slots
	void login();
	void logout();
	void registerStudent();
	void generateClassList();
};

#endif /* STUDENT_APP_H_ */
