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

	try { // initialize MySQL connection
		const std::string url = DEFAULT_URI;
		const std::string user = EXAMPLE_USER;
		const std::string pass = EXAMPLE_PASS;
		const std::string schema = EXAMPLE_DB;

		driver_ptr = sql::mysql::get_driver_instance(); // not thread safe
		/* Using the Driver to create a connection */
		cout << "Creating session on " << url << " ..."
				<< endl << endl;

		con_ptr = std::unique_ptr<sql::Connection>(driver_ptr->connect(url, user, pass));
		cout << "::StudentApplication Connection isValid: " << con_ptr->isValid() << endl;

		con_ptr->setSchema(schema);
	}  catch (sql::SQLException &e) {
		handle_SQLException(e);
	}

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

  // TODO do real authentication
  if(checkStudentUserId(userId.toUTF8()))
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

	  registerWidget->updateNumCourses();
	  registerButton->show();
	  generateClassListButton->show();
	  doneButton->hide();

	  m_isLoggedIn = true;
  } else {
	  greeting_->setText("Invalid Student Id: " + userId);
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
	registerWidget->cleanUp();

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

std::string StudentApplication::handle_SQLException(sql::SQLException &e)
{
	std::stringstream ss;

	/*
	 * 	The JDBC API throws three different exceptions:
	 *      - sql::MethodNotImplementedException (derived from sql::SQLException)
	 *      - sql::InvalidArgumentException (derived from sql::SQLException)
	 *      - sql::SQLException (derived from std::runtime_error)
	 */
	ss << "# ERR: SQLException in " << __FILE__;
	/* Use what() (derived from std::runtime_error) to fetch the error message */
	ss << "# ERR: " << e.what();
	ss << " (MySQL error code: " << e.getErrorCode();
	ss << ", SQLState: " << e.getSQLState() << " )" << endl;

	std::string output_string(ss.str());
	cout << output_string;
	return output_string;
}

bool StudentApplication::checkStudentUserId(std::string userId)
{
	bool ret_val = false;

	std::unique_ptr<sql::Statement> stmt(con_ptr->createStatement());
	std::string query_string =
			"SELECT S_ID\
			FROM	STUDENT\
			WHERE   S_ID = '" + userId + "';";

	std::unique_ptr<sql::ResultSet>	res(stmt->executeQuery(query_string));

	while(res->next())
	{
		ret_val = true;
	}

	return ret_val;
}
