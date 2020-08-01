INSERT INTO STAFF VALUES
('123-45-6789', 'John Smith', '1 Market St. Newark, NJ 07114', 'Faculty', 100000.00, 'FT', 4, NULL),
('987-65-4321', 'Leslie Knope', '2358 Highland Ave. Ramsey, NJ 07446', 'Faculty', 80000.00, 'FT', 3, NULL),
('573-82-0586', 'Jack Johnson', '287 High Way Franklin Lakes, NJ 07417', 'Teaching Assistant', 1000.00, 'FT', 2, 20),
('385-08-4170', 'Frank Sharp', '37 Tree St. Newark, NJ 07114', 'Faculty', 95000.00, 'FT', 3, NULL),
('936-63-1234', 'Barry Bonds', '84 Main St. Ramsey, NJ 07446', 'Faculty', 120000.00, 'FT', 5, NULL),
('946-47-3456', 'Chris Heinz', '74 Maple Ave. Oakland, NJ 07436', 'Teaching Assistant', 1000.00, 'FT',2, 20),
('045-36-2746', 'Mark Jacobs', '854 Mina Ave. Franklin Lakes, NJ 07417', 'Teaching Assistant', 500.00, 'PT', 1, 12),
('634-64-9220', 'Frank Sinatra', '35 Data Ave. Newark, NJ 07114', 'Faculty', 90000.00, 'FT', 4, NULL);

INSERT INTO BUILDING VALUES
('BDFMHL', 'Faculty Memorial', '50 Smith Rd. Newark, NJ 07103'), 
('BDLSHL', 'La Salle Hall', '30 Timber Lane Newark, NJ 07103'),
('BDKUPF', 'Kupfrian Hall', '100 Summit Ave. Newark, NJ 07103');

INSERT INTO ROOM VALUES
('BDFMHL', '123', 40, 'Projector, Smart Board'),
('BDFMHL', '45', 3, NULL),
('BDFMHL', '4525', 35, 'Projector'),
('BDFMHL', '98', 3, NULL),
('BDLSHL', '66', 100, 'Smart Board'),
('BDLSHL', '4564', 50, 'Smart Board'),
('BDLSHL', '273',3, NULL),
('BDLSHL', '274',3, NULL),
('BDKUPF', '53', 20, 'Projector, Smart Board'),
('BDKUPF', '464', 80,'Projector, Smart Board'),
('BDKUPF', '99', 3, NULL);

INSERT INTO DEPARTMENT VALUES
('DPCOMP', 'Computer Science', 473859.00, '123-45-6789', 'BDFMHL', '45'),
('DPFINC', 'Finance', 473859.00, '987-65-4321', 'BDFMHL', '98'),
('DPSTAT', 'Statistics', 986859.00, '385-08-4170', 'BDLSHL', '273'),
('DPBIOL', 'Biology', 623547.54, '936-63-1234', 'BDKUPF', '99'),
('DPMATH', 'Mathematics', 573947.34, '634-64-9220', 'BDLSHL', '274');

INSERT INTO STUDENT VALUES
('cb375', '837-24-9284', 'Chris Bazzini', '7 Main St. Oakland, NJ 07436', 'Don Bosco Prep', 3, 'DPCOMP'),
('lq25', '253-52-2455', 'Lauren Quense', '23 Franklin Ave. Ramsey, NJ 07446', 'Ramsey High School', 4, 'DPFINC'),
('db22', '354-36-4543', 'Daniela Barns', '14 Pine St. Wyckoff, NJ 07481', 'IHA', 2, 'DPSTAT'),
('js525', '254-54-2456', 'Josh Smith', '15 Apple Rd. Newark, NJ 07103', 'St. Benedicts', 4, 'DPMATH'),
('mp62', '234-64-2087', 'Mike Palta', '47 Saddle St. Ramsey, NJ 07446', 'Don Bosco Prep', 3, 'DPBIOL'),
('cr245', '345-64-2646', 'Charles Rondo', '23 East River Rd. Clifton, NJ 07014', 'Clifton High School', 2, 'DPMATH');

INSERT INTO COURSE VALUES
('CS100', 'Intro to Computer Science', 4.0, 6, 'DPCOMP'),
('CS200', 'Advanced Computer Programing', 4.0, 6, 'DPCOMP'),
('CS300', 'Intro to Database Systems', 4.0, 6, 'DPCOMP'),
('CS400', 'Advanced Database Systems', 4.0, 6, 'DPCOMP'),
('FN100', 'Intro to Finance', 3.0, 4, 'DPFINC'),
('FN200', 'Financial Accounting', 3.0, 4, 'DPFINC'),
('FN300', 'Financial Investments', 4.0, 6, 'DPFINC');

INSERT INTO SECTION VALUES
('CS100', '1001', 2020, 'Fall', '123-45-6789', 10, '045-36-2746'),
('CS100', '1002', 2020, 'Fall', '123-45-6789', 20, '045-36-2746'),
('CS200', '2001', 2020, 'Fall', '987-65-4321', 30, '573-82-0586');

INSERT INTO REGISTRATION VALUES
('cb375', 'CS100', '1001'),
('lq25', 'CS100', '1001'),
('db22', 'CS100', '1001'),
('js525', 'CS100', '1001'),
('mp62', 'CS100', '1001'),
('cr245', 'CS100', '1001');

INSERT INTO SECTION_IN_ROOM VALUES
('BDFMHL', '123', 'CS100', '1001', 'MWF', '1:30');
