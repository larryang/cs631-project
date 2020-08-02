/*
 * student-app.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#include "student-app.h"
#include <memory>

StudentApplication::StudentApplication() : Wt::WContainerWidget()
{
    greeting_ = addWidget(std::make_unique<Wt::WText>());
	addWidget(std::make_unique<Wt::WBreak>());

	{
		// hide this when logged in
		userIdText = addWidget(std::make_unique<Wt::WText>("Student Id: "));
		userIdEdit = addWidget(std::make_unique<Wt::WLineEdit>());
		addWidget(std::make_unique<Wt::WBreak>());
		passwordText = addWidget(std::make_unique<Wt::WText>("Password: "));
		passwordEdit = addWidget(std::make_unique<Wt::WLineEdit>());
		addWidget(std::make_unique<Wt::WBreak>());

		// which one to display depends on m_isLoggedIn
		loginButton = addWidget(std::make_unique<Wt::WPushButton>("Login"));
		logoutButton = addWidget(std::make_unique<Wt::WPushButton>("Logout"));
		logoutButton->hide();
		addWidget(std::make_unique<Wt::WBreak>());
		addWidget(std::make_unique<Wt::WBreak>());
	}
	{
		registerWidget = addWidget(std::make_unique<StudentRegisterWidget>(this));
		registerWidget->hide();
		registerButton = addWidget(std::make_unique<Wt::WPushButton>("Register for Course"));
		registerButton->hide();
	}
	{
		generateClassListWidget = addWidget(std::make_unique<ClassListGenerateWidget>(this));
		generateClassListWidget->hide();
		generateClassListButton = addWidget(std::make_unique<Wt::WPushButton>("List Class Info"));
		generateClassListButton->hide();
	}
	{
		doneButton = addWidget(std::make_unique<Wt::WPushButton>("Done"));
		doneButton->hide();
	}

	loginButton->clicked().connect(this, &StudentApplication::login);
	logoutButton->clicked().connect(this, &StudentApplication::logout);
	registerButton->clicked().connect(this, &StudentApplication::registerStudent);
	generateClassListButton->clicked().connect(this, &StudentApplication::generateClassList);
	doneButton->clicked().connect(this, &StudentApplication::done);
}

std::string StudentApplication::studentId()
{
	return m_userId.toUTF8();
}

void StudentApplication::login()
{
  // TODO check password
  Wt::WString userId = userIdEdit->text();
  Wt::WString password = passwordEdit->text();

  if(userId == "abc123" && password == "password")
  {
	  m_userId = userId;
	  m_password = password;
	  greeting_->setText("Hello, " + m_userId);

	  userIdText->hide();
	  userIdEdit->hide();
	  passwordText->hide();
	  passwordEdit->hide();

	  loginButton->hide();
	  logoutButton->show();
	  addWidget(std::make_unique<Wt::WBreak>());
	  addWidget(std::make_unique<Wt::WBreak>());

	  registerButton->show();
	  generateClassListButton->show();
	  doneButton->hide();

	  m_isLoggedIn = true;
  }
}

void StudentApplication::logout()
{
	m_userId = "";
	m_password = "";
	m_isLoggedIn = false;

	userIdText->show();
	userIdEdit->show();
	passwordText->show();
	passwordEdit->show();

	loginButton->show();
	logoutButton->hide();

	registerWidget->hide();
	registerButton->hide();

	generateClassListWidget->hide();
	generateClassListButton->hide();
}

void StudentApplication::done()
{
	registerWidget->hide();
	generateClassListWidget->hide();

	registerButton->show();
	generateClassListButton->show();
	doneButton->hide();
}

void StudentApplication::registerStudent()
{
	registerButton->hide();
	generateClassListButton->hide();
	registerWidget->show();

	doneButton->show();
}

void StudentApplication::generateClassList()
{
	registerButton->hide();
	generateClassListButton->hide();
	generateClassListWidget->show();

	doneButton->show();
}

