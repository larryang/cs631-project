INCLUDES =	-I/usr/include/mysql-cppconn-8 -I./

CXXFLAGS =	${INCLUDES} -O3 -g -Wall -Wextra -pedantic -fmessage-length=0 -std=c++14

OBJS =		studentRegister.o classListGenerate.o student-app.o student-main.o 

LIBS =		-lwthttp -lwt -lmysqlcppconn

TARGET =	student-main

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
