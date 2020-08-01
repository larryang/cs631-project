INCLUDES =	-I/usr/include/mysql-cppconn-8 -I./

CXXFLAGS =	${INCLUDES} -O2 -g -Wall -fmessage-length=0 -std=c++14

OBJS =		student-app.o student-main.o

LIBS =		-lwthttp -lwt -lmysqlcppconn

TARGET =	student-main

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
