Have to use JDBC, because that's what NJIT supports.

download lastest https://dev.mysql.com/downloads/connector/cpp/ for Ubuntu Linux

Debian packages are available for Linux (as of Connector/C++ 8.0.14). The packages are distinguished by their base names (the full names include the Connector/C++ version and suffixes):
    libmysqlcppconn8-1: This package provides the shared connector library implementing X DevAPI and X DevAPI for C.
        libmysqlcppconn7: This package provides the shared legacy connector library implementing the JDBC API.
	    libmysqlcppconn-dev: This package installs development files required for building applications that use Connector/C++ libraries provided by the other packages, and static connector libraries. This package depends on the shared libraries provided by the other packages. It cannot be installed by itself without the other two packages.

To download:
wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn7_8.0.21-1ubuntu20.04_amd64.deb
wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn-dev_8.0.21-1ubuntu20.04_amd64.deb

sudo apt install ./libmysqlcppconn7_8.0.21-1ubuntu20.04_amd64.deb ./libmysqlcppconn-dev_8.0.21-1ubuntu20.04_amd64.deb

Code examples:
 https://dev.mysql.com/doc/dev/connector-cpp/8.0/jdbc_ref.html
  https://dev.mysql.com/doc/connector-cpp/1.1/en/connector-cpp-getting-started-examples.html

Compile: g++ -I/usr/include/mysql-cppconn-8 test_mysql.cpp -o test_mysql -lmysqlcppconn
