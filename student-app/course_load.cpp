

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
		int num_courses, max_enroll, enrolled_students, course_limit = 5;
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
				//query to check if the course and section actually exists
				std::unique_ptr<sql::ResultSet>
				c_s_check (stmt-> executeQuery("SELECT Course_ID, Sec_No FROM SECTION WHERE Course_ID = '" + course_id + "' and Sec_No = '" + sec_num + "'"));
				if (c_s_check -> next()){
					cout << "This course exists" << endl;
					//query to check if the student is already in the course they are trying to register for
					std::unique_ptr<sql::Statement> stmt2(con_ptr->createStatement());
					std::unique_ptr<sql::ResultSet>
					res2 (stmt2->executeQuery("SELECT S_ID FROM REGISTRATION WHERE S_ID = '" + student_id + "' AND Course_ID = '" + course_id + "'"));
					if(res2->next())
						cout << "You are already registered for this course. Please choose another." << endl;
				
					else{
						//checks if class is full
						cout << "Checking if class is full" << endl;
						std::unique_ptr<sql::Statement> stmt3(con_ptr->createStatement());
		                                std::unique_ptr<sql::ResultSet>
		                                full (stmt3->executeQuery("SELECT r.course_id, r.sec_no, count(s_id) AS NumStud, Max_Enroll FROM REGISTRATION r, SECTION s WHERE r.course_Id = '" + course_id + "' AND r.sec_no = '" + sec_num + "' AND r.Course_ID = s.course_id AND r.sec_no = s.sec_no GROUP BY r.course_id, s.sec_no"));

					while(full -> next()){
					        enrolled_students = full-> getInt("NumStud");
		                		max_enroll = full-> getInt("Max_Enroll");
					}
						
						int seats_left = max_enroll - enrolled_students;
			                        if (seats_left > 0){
				                       	cout << "You can enroll for this course!";
			        	               	cout << "There are " << seats_left << " seats left!" << endl;
							cout << "Registering you for Course: " << course_id << ", Section: " << sec_num << endl;
				        		std::unique_ptr<sql::Statement> stmt4(con_ptr->createStatement());
							stmt4->executeUpdate("INSERT INTO REGISTRATION VALUES ('" + student_id + "', '" + course_id + "', '" + sec_num + "')");
							num_courses += 1;
							cout << "You have registered for " << num_courses << " classes." << endl;
						}	
						else
							cout << "Sorry, this class is full. Please select another course." << endl;
					}			
				}
				else
					cout << "This course does not exists" << endl;
			}
			else{
				cout << "Thank you for registering." << endl;
				break;
			}
		}
	if (num_courses == course_limit)
		cout << "You are already registered for all of your courses. Thank you have a nice day." << endl;	

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


