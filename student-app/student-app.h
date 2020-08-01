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

	// Slots
	void login();
	void logout();
	void registerStudent();
	void listSection();
};

#endif /* STUDENT_APP_H_ */
