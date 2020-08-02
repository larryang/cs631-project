# get list of section and info
SELECT 	S.Course_ID, S.Sec_No, C.Course_Name, R.Meet_days, R.Meet_time, R.Building_ID, R.Room_no, STAFF.T_Name
FROM    SECTION S, COURSE C, SECTION_IN_ROOM R, STAFF 
WHERE   S.Course_ID = C.Course_ID
	AND S.Course_ID = R.Course_ID
	AND S.Sec_No = R.Sec_No
	AND S.T_SSN = STAFF.T_SSN;

# query model for looping over list of sections
SELECT	s.S_LName, s.S_FName, s.S_ID, s.Major, S_Year  
FROM 	STUDENT s, REGISTRATION r
WHERE	s.S_ID = r.S_ID
	AND r.COURSE_ID = "CS100"
	AND r.Sec_No = "1001";
