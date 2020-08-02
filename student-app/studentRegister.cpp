/*
 * studentRegister.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */
#include "studentRegister.h"
#include "Wt/WBreak.h"
#include "connectMySql.h"

StudentRegisterWidget::StudentRegisterWidget(StudentApplication* parent) : Wt::WContainerWidget()
{
	m_parent = parent;

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
		cout << "Student Register Connection isValid: " << con_ptr->isValid() << endl;

		con_ptr->setSchema(schema);
	}  catch (sql::SQLException &e) {
		handle_SQLException(e);
	}

	addWidget(std::make_unique<Wt::WText>("Register student for a course"));
	addWidget(std::make_unique<Wt::WBreak>());
	addWidget(std::make_unique<Wt::WBreak>());
	numCourses = addWidget(std::make_unique<Wt::WText>());
	updateNumCourses();
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

	addWidget(std::make_unique<Wt::WBreak>());
	queryResponse = addWidget(std::make_unique<Wt::WText>());

	registerCourseButton->clicked().connect(this, &StudentRegisterWidget::registerCourse);
}

void StudentRegisterWidget::handle_SQLException(sql::SQLException &e) {
	/*
	 * 	The JDBC API throws three different exceptions:
	 *      - sql::MethodNotImplementedException (derived from sql::SQLException)
	 *      - sql::InvalidArgumentException (derived from sql::SQLException)
	 *      - sql::SQLException (derived from std::runtime_error)
	 */
	cout << "# ERR: SQLException in " << __FILE__;
	cout << "(" << "main()" << ") on line " << __LINE__ << endl;
	/* Use what() (derived from std::runtime_error) to fetch the error message */
	cout << "# ERR: " << e.what();
	cout << " (MySQL error code: " << e.getErrorCode();
	cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}

int StudentRegisterWidget::updateNumCourses()
{
	int num_courses = 0;

	const std::string student_id = m_parent->studentId();

	//query to check number of classes the student is registered
	cout << "running ::updateNumCourses()" << endl;
	std::stringstream num_classes;
	std::unique_ptr<sql::Statement> stmt(con_ptr->createStatement());
	std::unique_ptr<sql::ResultSet>
	res (stmt->executeQuery("SELECT s_id, count(*) AS NumClass FROM REGISTRATION WHERE S_ID = '" + student_id + "'"));

	while(res->next()){
		num_courses = res -> getInt("NumClass");
		num_classes << "You are currently enrolled in " << num_courses << " courses." << endl;
	}

	numCourses->setText(num_classes.str());
	return num_courses;
}

void StudentRegisterWidget::registerCourse()
{
	// get query input
	const std::string student_id = m_parent->studentId();
	const std::string course_id = courseCodeEdit->text().toUTF8();
	const std::string time = timeEdit->text().toUTF8();
	const std::string sec_num = sectionNumberEdit->text().toUTF8();

	// declare query output
	std::string output_text;

	try
	{
		int num_courses = updateNumCourses();
		char reg;

	} catch (sql::SQLException &e) {
		handle_SQLException(e);
	}


	// do MySQL query - put output into this output_text string
	output_text = "Query not implemented yet. StudentID: " + m_parent->studentId()
			+ " CourseCode: " + course_id + " Time: " + time + " SectionNumber: " + sec_num;

	queryResponse->setText(output_text);
}
