#include <memory>
#include <mysql/jdbc.h> 

using std::cout;
using std::endl;

int main(void)
{
  cout << endl;
  cout << "Connector/C++ standalone program example..." << endl;
  cout << endl;

  #define DEFAULT_URI "tcp://sql.njit.edu"
  #define EXAMPLE_USER "ly23"
  #define EXAMPLE_PASS "Datalarryn0w@"
  #define EXAMPLE_DB "ly23"

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

      con_ptr->setSchema(schema);

      std::unique_ptr<sql::Statement> stmt(con_ptr->createStatement());
      std::unique_ptr<sql::ResultSet>
	res(stmt->executeQuery("SELECT 'Welcome to Connector/C++' AS _message"));
      cout << "\t... running 'SELECT 'Welcome to Connector/C++' AS _message'"
	   << endl;
      while (res->next())
	{
	  cout << "\t... MySQL replies: " << res->getString("_message") << endl;
	  cout << "\t... say it again, MySQL" << endl;
	  cout << "\t....MySQL replies: " << res->getString(1) << endl;
	}
 

  } catch (sql::SQLException &e) {
    /*
      The JDBC API throws three different exceptions:
    - sql::MethodNotImplementedException (derived from sql::SQLException)
    - sql::InvalidArgumentException (derived from sql::SQLException)
    - sql::SQLException (derived from std::runtime_error)
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
