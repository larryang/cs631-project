/*
 * student-app.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#include "student-app.h"

StudentApplication::StudentApplication(const Wt::WEnvironment& env) : WApplication(env)
{
	setTitle("Student Application");

    greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
	root()->addWidget(std::make_unique<Wt::WBreak>());

	// hide this when logged in
	userIdText = root()->addWidget(std::make_unique<Wt::WText>("Student Id: "));
	userIdEdit = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	root()->addWidget(std::make_unique<Wt::WBreak>());
	passwordText = root()->addWidget(std::make_unique<Wt::WText>("Password: "));
	passwordEdit = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	root()->addWidget(std::make_unique<Wt::WBreak>());

	// which one to display depends on m_isLoggedIn
	loginButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Login"));
	logoutButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Logout"));
	logoutButton->hide();

	loginButton->clicked().connect(this, &StudentApplication::login);
	logoutButton->clicked().connect(this, &StudentApplication::logout);
}


void StudentApplication::login()
{
  // TODO check password
  m_userId = userIdEdit->text();
  m_password = passwordEdit->text();
  greeting_->setText("Hello, " + m_userId);

  userIdText->hide();
  userIdEdit->hide();
  passwordText->hide();
  passwordEdit->hide();

  loginButton->hide();
  logoutButton->show();

  m_isLoggedIn = true;
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

