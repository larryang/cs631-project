

#include <stdlib.h>
#include <memory>
#include <iostream>
#include <mysql/jdbc.h> 
#include <string>


using std::cout;
using std::cin;
using std::endl;

int main(void)
{
	cout << endl;
	cout << "Connector/C++ standalone program example..." << endl;
	cout << endl;
 
	#define DEFAULT_URI "tcp://sql.njit.edu"
	#define EXAMPLE_USER "cb375"
	#define EXAMPLE_PASS "Kq&AN#8N%3"
	#define EXAMPLE_DB "cb375"


	const std::string url = DEFAULT_URI;
	const std::string user = EXAMPLE_USER;
	const std::string pass = EXAMPLE_PASS;
	const std::string schema = EXAMPLE_DB;

	try
	{
		sql::Driver *driver_ptr = sql::mysql::get_driver_instance(); // not thread safe
		/* Using the Driver to create a connection */
		cout << "Creating session on " << url << " ..."
		 	   << endl << endl;

		std::unique_ptr<sql::Connection> con_ptr(driver_ptr->connect(url, user, pass));
		cout << "Conection isValid: " << con_ptr->isValid() << endl;

		std::string course_id, sec_num, student_id, pswd;
		int num_courses, course_limit = 5;
		char reg;

		cout << "Please enter your Student ID: ";
		cin >> student_id;
		cout << "Password: ";
		cin >> pswd;
		cout << "Checking credentials....\n" << endl;
		cout << "Login successful!" << endl;

		con_ptr->setSchema(schema);
		
		
		//query to check number of classes the student is registered
		std::unique_ptr<sql::Statement> stmt(con_ptr->createStatement());
		std::unique_ptr<sql::ResultSet>
		res (stmt->executeQuery("SELECT s_id, count(*) AS NumClass FROM REGISTRATION WHERE S_ID = '" + student_id + "'"));


		while(res->next()){
			num_courses = res -> getInt("NumClass");
			cout << "You are currently enrolled in " << num_courses << " courses." << endl;
		}
		
		while(num_courses < course_limit){
			cout << "Would you like to register for more courses? (Y/N)";
			cin >> reg;
			if (reg =='Y' || reg == 'y'){
		        	cout << "Please enter a Course ID: ";
				cin >> course_id;
				cout << "Please enter a Section Number: ";
				cin >> sec_num;
				//query to check if the student is already in the course they are trying to register for
				std::unique_ptr<sql::Statement> stmt2(con_ptr->createStatement());
				std::unique_ptr<sql::ResultSet>
				res2 (stmt2->executeQuery("SELECT S_ID FROM REGISTRATION WHERE S_ID = '" + student_id + "' AND Course_ID = '" + course_id + "'"));
				if(res2->next())
					cout << "You are already registered for this course. Please choose another." << endl;
				
				else{
					cout << "Registering you for Course: " << course_id << ", Section: " << sec_num << endl;
					std::unique_ptr<sql::Statement> stmt3(con_ptr->createStatement());
                                        stmt3->executeUpdate("INSERT INTO REGISTRATION VALUES ('" + student_id + "', '" + course_id + "', '" + sec_num + "')");
					num_courses += 1;
				}

				if(num_courses == 5)
					cout << "You have reached the limit of classes you can register for." << endl;
			}
			else
				break;
		}


		/*
		while(res->next()){
			cout << "Course ID = " << res -> getString("Course_Id");
			cout << ", Section Number = " << res -> getString("Sec_No");
			enrolled_students = res-> getInt("NumStud");
			cout << ", Number of Students = " << enrolled_students;
			max_enroll = res-> getInt("Max_Enroll");
			cout << ", Maximum number of students = " << max_enroll << endl;
			
			int seats_left = max_enroll - enrolled_students;
			if (seats_left > 0){
				cout << "You can enroll for this course!";
				cout << "There are " << seats_left << " seats left!" << endl;
				//insert into table
			}
			else
				cout << "Sorry this course is full." <<endl;
		}
		*/
			


	} catch (sql::SQLException &e) {
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
		return EXIT_FAILURE;
	}
}


