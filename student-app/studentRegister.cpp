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
		cout << "::StudentRegisterWidget Connection isValid: " << con_ptr->isValid() << endl;

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
	/* Use what() (derived from std::runtime_error) to fetch the error message */
	ss << "# ERR: " << e.what();
	ss << " (MySQL error code: " << e.getErrorCode();
	ss << ", SQLState: " << e.getSQLState() << " )" << endl;

	std::string output_string(ss.str());
	cout << output_string;
	return output_string;
}

void StudentRegisterWidget::cleanUp()
{
	queryResponse->setText("");
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
	std::stringstream ss;

	cout << "running ::registerCourse()" << endl;
	try
	{
		const int num_courses = updateNumCourses();
		bool error = false;

		if(course_limit <= num_courses)
		{
			ss << "You have reached the limit of classes you can register for." << endl;
			error = true;
		}

		if(!error) {
			//query to check if the course and section actually exists
			std::unique_ptr<sql::Statement> stmt(con_ptr->createStatement());
			std::unique_ptr<sql::ResultSet>
			c_s_check (stmt-> executeQuery("SELECT Course_ID, Sec_No FROM SECTION WHERE Course_ID = '" + course_id + "' and Sec_No = '" + sec_num + "'"));
			if (c_s_check -> next())
			{
				cout << "This course exists" << endl;

				//query to check if the student is already in the course they are trying to register for
				std::unique_ptr<sql::Statement> stmt2(con_ptr->createStatement());
				std::unique_ptr<sql::ResultSet>
				res2 (stmt2->executeQuery("SELECT S_ID FROM REGISTRATION WHERE S_ID = '" + student_id + "' AND Course_ID = '" + course_id + "'"));
				if(res2->next())
				{
					ss << "You are already registered for this course. Please choose another." << endl;
				} else{
					//checks if class is full
					cout << "Checking if class is full" << endl;
					std::unique_ptr<sql::Statement> stmt3(con_ptr->createStatement());
					std::unique_ptr<sql::ResultSet>
					full (stmt3->executeQuery("SELECT r.course_id, r.sec_no, count(s_id) AS NumStud, Max_Enroll FROM REGISTRATION r, SECTION s WHERE r.course_Id = '" + course_id + "' AND r.sec_no = '" + sec_num + "' AND r.Course_ID = s.course_id AND r.sec_no = s.sec_no GROUP BY r.course_id, s.sec_no"));

					int max_enroll = 0, enrolled_students = 0;
					while(full -> next()){
						enrolled_students = full-> getInt("NumStud");
						max_enroll = full-> getInt("Max_Enroll");
					}

					int seats_left = max_enroll - enrolled_students;
					if (seats_left > 0){
						ss << "You can enroll for this course!";
						ss << "There are " << seats_left << " seats left!" << endl;
						ss << "Registering you for Course: " << course_id << ", Section: " << sec_num << endl;
						std::unique_ptr<sql::Statement> stmt4(con_ptr->createStatement());
						stmt4->executeUpdate("INSERT INTO REGISTRATION VALUES ('" + student_id + "', '" + course_id + "', '" + sec_num + "')");
					}
					else
						ss << "Sorry, this class is full. Please select another course." << endl;
				}
			} else {
				ss << "This course does not exist" << endl;
			}
		}
	} catch (sql::SQLException &e) {
		ss << handle_SQLException(e);
	}


	// do MySQL query - put output into this output_text string
//	output_text = "Query not implemented yet. StudentID: " + m_parent->studentId()
//			+ " CourseCode: " + course_id + " Time: " + time + " SectionNumber: " + sec_num;
	Wt::WString output_text = Wt::WString::fromUTF8(ss.str());
	queryResponse->setText(output_text);
}
