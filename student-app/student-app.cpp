/*
 * student-app.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#include "student-app.h"

StudentApplication::StudentApplication() : Wt::WContainerWidget()
{
    greeting_ = addWidget(std::make_unique<Wt::WText>());
	addWidget(std::make_unique<Wt::WBreak>());

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

	loginButton->clicked().connect(this, &StudentApplication::login);
	logoutButton->clicked().connect(this, &StudentApplication::logout);
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
}

