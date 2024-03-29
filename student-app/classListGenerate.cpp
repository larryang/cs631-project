/*
 * classlistGenerate.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#include "classListGenerate.h"
#include <Wt/WBreak.h>

using std::cout;
using std::endl;

ClassListGenerateWidget::ClassListGenerateWidget(StudentApplication *parent) : Wt::WContainerWidget()
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
		cout << "::ClassListGenerateWidget Connection isValid: " << con_ptr->isValid() << endl;

		con_ptr->setSchema(schema);
	}  catch (sql::SQLException &e) {
		handle_SQLException(e);
	}

	setContentAlignment(Wt::AlignmentFlag::Left);

	addWidget(std::make_unique<Wt::WText>("Generate a class list for each section."));

	addWidget(std::make_unique<Wt::WBreak>());
	addWidget(std::make_unique<Wt::WBreak>());

	generateClassListButton = addWidget(std::make_unique<Wt::WPushButton>("Generate Class List"));
	addWidget(std::make_unique<Wt::WBreak>());

	queryResponse = addWidget(std::make_unique<Wt::WText>());
	addWidget(std::make_unique<Wt::WBreak>());

	table = addWidget(std::make_unique<Wt::WTable>());

	generateClassListButton->clicked().connect(this, &ClassListGenerateWidget::generateClassList);
}

std::string ClassListGenerateWidget::handle_SQLException(sql::SQLException &e) {
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



void ClassListGenerateWidget::generateClassList()
{
	std::stringstream ss;

	cout << "running ::ClassListGenerateWidget()" << endl;
	try {
		std::unique_ptr<sql::Statement> stmt(con_ptr->createStatement());
		//std::unique_ptr<sql::ResultSet> res("SELECT S_ID FROM REGISTRATION WHERE S_ID = '" + student_id + "' AND Course_ID = '" + course_id + "'");
		std::string query_string =
				"SELECT 	S.Course_ID, S.Sec_No, C.Course_Name, R.Meet_days, R.Meet_time, R.Building_ID, R.Room_no, STAFF.T_Name\
		     FROM    SECTION S, COURSE C, SECTION_IN_ROOM R, STAFF\
			 WHERE   S.Course_ID = C.Course_ID\
			 AND S.Course_ID = R.Course_ID\
			 AND S.Sec_No = R.Sec_No\
			 AND S.T_SSN = STAFF.T_SSN;";
		std::unique_ptr<sql::ResultSet>	res(stmt->executeQuery(query_string));

		int row = 0;
		table->clear();
		while(res->next())
		{
			std::string courseId = res->getString("Course_ID").asStdString();
			std::string courseName = res->getString("Sec_No").asStdString();

			table->elementAt(row, 0)->addWidget(std::make_unique<Wt::WText>(courseId));
			table->elementAt(row, 1)->addWidget(std::make_unique<Wt::WText>(courseName));
			table->elementAt(row, 2)->addWidget(std::make_unique<Wt::WText>(res->getString("Course_Name").c_str()));
			table->elementAt(row, 3)->addWidget(std::make_unique<Wt::WText>(res->getString("Meet_days").c_str()));
			table->elementAt(row, 4)->addWidget(std::make_unique<Wt::WText>(res->getString("Meet_time").c_str()));
			table->elementAt(row, 5)->addWidget(std::make_unique<Wt::WText>(res->getString("Building_ID").c_str()));
			table->elementAt(row, 6)->addWidget(std::make_unique<Wt::WText>(res->getString("Room_no").c_str()));
			table->elementAt(row, 7)->addWidget(std::make_unique<Wt::WText>(res->getString("T_Name").c_str()));
			++row;

			std::unique_ptr<sql::Statement> student_stmt(con_ptr->createStatement());
			std::string student_query_string =
					"SELECT	s.S_LName, s.S_FName, s.S_ID, s.Major, s.S_Year\
					FROM 	STUDENT s, REGISTRATION r\
					WHERE	s.S_ID = r.S_ID\
						AND r.COURSE_ID = '" + courseId + "'\
						AND r.Sec_No = '" + courseName + "'\
					ORDER BY s.S_LName;";

			cout << student_query_string << endl;
			std::unique_ptr<sql::ResultSet>	student_res(student_stmt->executeQuery(student_query_string));
			while(student_res->next())
			{
				table->elementAt(row, 1)->addWidget(std::make_unique<Wt::WText>(student_res->getString("S_LName").c_str()));
				table->elementAt(row, 2)->addWidget(std::make_unique<Wt::WText>(student_res->getString("S_FName").c_str()));
				table->elementAt(row, 3)->addWidget(std::make_unique<Wt::WText>(student_res->getString("S_ID").c_str()));
				table->elementAt(row, 4)->addWidget(std::make_unique<Wt::WText>(student_res->getString("Major").c_str()));
				table->elementAt(row, 5)->addWidget(std::make_unique<Wt::WText>(std::to_string(student_res->getInt("S_Year")).c_str()));
				++row;
			}
		}
	} catch (sql::SQLException &e) {
		ss << handle_SQLException(e);
	}

	// run the SQL query and stuff it into string
	std::string output_string = ss.str();

	queryResponse->setText(output_string);
}

