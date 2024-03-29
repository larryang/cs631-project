CREATE SCHEMA njit_student_registration;

CREATE TABLE STAFF
(T_SSN CHAR(11) NOT NULL,
T_Name CHAR(40),
T_ADD VARCHAR(50),
T_Function CHAR(25),
T_Salary DECIMAL(8,2),
TA_Rank CHAR(2),
Course_Load INT,
Work_hr INT,

PRIMARY KEY (T_SSN));

CREATE TABLE BUILDING
(Building_ID CHAR(6) NOT NULL,
B_Name CHAR(30),
Location VARCHAR(50),

PRIMARY KEY (Building_ID));

CREATE TABLE ROOM
(Building_ID CHAR(6) NOT NULL,
Room_No CHAR(4) NOT NULL,
Capacity INT,
Audio_Visual CHAR(50),

CONSTRAINT PK_Room PRIMARY KEY (Building_ID, Room_No));

CREATE TABLE DEPARTMENT
(Dept_Code VARCHAR(6) NOT NULL,
Dept_Name CHAR(25),
A_Budget DECIMAL(10,2) DEFAULT 0.00
	CHECK (A_BUDGET >= 0),
Dept_Chair CHAR(11),
Dept_Location_Building CHAR(6),
Dept_Location_Room CHAR(4),

PRIMARY KEY (Dept_Code),

FOREIGN KEY (Dept_Chair) REFERENCES STAFF(T_SSN)
	ON DELETE SET NULL,
CONSTRAINT FK_Room FOREIGN KEY (Dept_Location_Building, Dept_Location_Room) REFERENCES ROOM(Building_ID, Room_No));


CREATE TABLE STUDENT
(S_ID VARCHAR(6) NOT NULL,
S_SSN CHAR(11),
S_FName CHAR(20),
S_LName CHAR(20),
S_Add VARCHAR(50),
S_High VARCHAR(40),
S_Year INT,
Major VARCHAR(6),
PRIMARY KEY (S_ID),

FOREIGN KEY (Major) REFERENCES DEPARTMENT(Dept_Code)
	ON UPDATE CASCADE
    ON DELETE SET NULL);

CREATE TABLE COURSE
(Course_ID VARCHAR(6) NOT NULL,
Course_Name CHAR(30),
Credit DECIMAL(2,1),
TA_hr_req DECIMAL(3,1),
Dept_Code VARCHAR(6),

PRIMARY KEY (Course_ID),

FOREIGN KEY (Dept_Code) REFERENCES DEPARTMENT(Dept_Code)
	ON UPDATE CASCADE);

CREATE TABLE SECTION
(Course_ID VARCHAR(6) NOT NULL,
Sec_No CHAR(4) NOT NULL,
Year_Offered INT,
Semester CHAR(6),
T_SSN CHAR(11),
Max_Enroll INT,
Assistant_SSN CHAR(11),

CONSTRAINT PK_Section PRIMARY KEY (Course_ID, Sec_No)
);

CREATE TABLE REGISTRATION
(S_ID VARCHAR(6) NOT NULL,
Course_ID VARCHAR(6) NOT NULL,
Sec_No INT NOT NULL,

CONSTRAINT PK_Registration PRIMARY KEY (S_ID, Course_ID, Sec_No)
);

CREATE TABLE SECTION_IN_ROOM
(Building_ID CHAR(6) NOT NULL,
Room_No CHAR(4) NOT NULL,
Course_ID VARCHAR(6) NOT NULL,
Sec_No INT NOT NULL,
Meet_days CHAR(4),
Meet_time TIME(0),

CONSTRAINT PK_Sec_Room PRIMARY KEY (Building_ID, Room_No, Course_ID, Sec_No)
);
