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
	updateNumCourses();
}

std::string StudentRegisterWidget::handle_SQLException(sql::SQLException &e) {
	std::stringstream ss;

	/*
	 * 	The JDBC API throws three different exceptions:
	 *      - sql::MethodNotImplementedException (derived from sql::SQLException)
	 *      - sql::InvalidArgumentException (derived from sql::SQLException)
	 *      - sql::SQLException (derived from std::runtime_error)
	 */
	ss << "# ERR: SQLException in " << __FILE__;
	ss << "(" << "main()" << ") on line " << __LINE__ << endl;
	/* Use what() (derived from std::runtime_error) to fetch the error message */
	ss << "# ERR: " << e.what();
	ss << " (MySQL error code: " << e.getErrorCode();
	ss << ", SQLState: " << e.getSQLState() << " )" << endl;

	std::string output_string(ss.str());
	cout << output_string;
	return output_string;
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
		num_classes << "You are currently enrolled in " << num_courses
				<< " courses of out " <<  course_limit << endl;
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

	cout << "running ::registerCourse()" << endl;
	try
	{
		int num_courses = updateNumCourses();

		if(course_limit <= num_courses)
		{
			output_text = "You have reached the limit of classes you can register for.";
		} else {
			//query to check if the student is already in the course they are trying to register for
			std::unique_ptr<sql::Statement> stmt2(con_ptr->createStatement());
			std::unique_ptr<sql::ResultSet>
			res2 (stmt2->executeQuery("SELECT S_ID FROM REGISTRATION WHERE S_ID = '" + student_id + "' AND Course_ID = '" + course_id + "'"));
			if(res2->next())
				output_text = "You are already registered for this course. Please choose another.";

			else{
				cout << "Registering you for Course: " << course_id << ", Section: " << sec_num << endl;
				std::unique_ptr<sql::Statement> stmt3(con_ptr->createStatement());
				stmt3->executeUpdate("INSERT INTO REGISTRATION VALUES ('" + student_id + "', '" + course_id + "', '" + sec_num + "')");
				num_courses = updateNumCourses();
			}
		}
	} catch (sql::SQLException &e) {
		output_text = handle_SQLException(e);
	}


	// do MySQL query - put output into this output_text string
//	output_text = "Query not implemented yet. StudentID: " + m_parent->studentId()
//			+ " CourseCode: " + course_id + " Time: " + time + " SectionNumber: " + sec_num;
	queryResponse->setText(output_text);
}
