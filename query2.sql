#Created what the queries would be for Question 2 in just SQL.
#I hardcoded the course and sec id for now to test, but obviously this would be populated based on search



SELECT s.course_id, s.sec_no, c.course_name, sr.meet_time, sr.building_ID, sr.room_no, sr.meet_days, t_name
FROM COURSE c, SECTION s, SECTION_IN_ROOM sr, staff
WHERE c.Course_ID =  'CS100'
AND s.Sec_No = '1001'
AND c.course_id = s.course_id
AND s.course_id = sr.course_id
AND s.sec_no = sr.sec_no
AND s.t_SSN = staff.t_ssn;


SELECT s.S_ID, S_FName, Major, S_Year
FROM STUDENT s, REGISTRATION r
WHERE s.s_id = r.s_id
AND r.Course_ID =  'CS100'
AND r.Sec_No = '1001'
ORDER BY S_LName;
