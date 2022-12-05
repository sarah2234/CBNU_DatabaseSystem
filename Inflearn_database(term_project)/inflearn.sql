CREATE DATABASE inflearn;

USE inflearn;

CREATE TABLE User(
user_id CHAR(10) NOT NULL,
nickname CHAR(10) NOT NULL,
password CHAR(20) NOT NULL,
PRIMARY KEY (user_id),
UNIQUE KEY nickname (nickname)
);

CREATE TABLE Coupon_Name(
coupon_id CHAR(10) NOT NULL,
coupon_name VARCHAR(255) NOT NULL,
PRIMARY KEY (coupon_id)
);

CREATE TABLE Coupon_Info(
coupon_name VARCHAR(255) NOT NULL,
expiration_date DATE NOT NULL,
discount INT NOT NULL,
PRIMARY KEY (coupon_name)
);

CREATE TABLE Instructor(
instructor_id CHAR(10) NOT NULL,
instructor_name CHAR(10) NOT NULL,
password CHAR(20) NOT NULL,
introduction TEXT,
PRIMARY KEY (instructor_id),
UNIQUE KEY (instructor_name)
);

CREATE TABLE Category(
name CHAR(10) NOT NULL,
PRIMARY KEY (name)
);

CREATE TABLE Curriculum(
instructor_id CHAR(10) NOT NULL,
curriculum_name VARCHAR(50) NOT NULL,
price FLOAT NOT NULL,
category CHAR(10),
FOREIGN KEY (instructor_id) REFERENCES Instructor (instructor_id),
FOREIGN KEY (category) REFERENCES Category (name),
PRIMARY KEY (instructor_id, curriculum_name)
);

CREATE TABLE Lecture(
instructor_id CHAR(10) NOT NULL,
curriculum_name VARCHAR(50) NOT NULL,
lecture_name VARCHAR(50) NOT NULL,
length INT(9) UNSIGNED DEFAULT 0,
PRIMARY KEY (instructor_id, curriculum_name, lecture_name)
);
ALTER TABLE Lecture
ADD FOREIGN KEY (instructor_id, curriculum_name)
REFERENCES Curriculum (instructor_id, curriculum_name)
ON DELETE CASCADE;

CREATE TABLE Orders(
user_id CHAR(10) NOT NULL,
order_id INT(9) UNSIGNED NOT NULL,
PRIMARY KEY (user_id, order_id)
);

CREATE TABLE Orders_Curriculum(
user_id CHAR(10) NOT NULL,
order_id INT(9) UNSIGNED NOT NULL,
instructor_id CHAR(10) NOT NULL,
curriculum_name VARCHAR(50) NOT NULL,
FOREIGN KEY (user_id, order_id)
REFERENCES Orders (user_id, order_id) ON DELETE CASCADE,
FOREIGN KEY (instructor_id, curriculum_name)
REFERENCES Curriculum (instructor_id, curriculum_name) ON DELETE CASCADE,
PRIMARY KEY (order_id, user_id, instructor_id, curriculum_name)
);

CREATE TABLE Orders_Coupon(
user_id CHAR(10) NOT NULL,
order_id INT(9) UNSIGNED NOT NULL,
coupon_id CHAR(16) NOT NULL,
FOREIGN KEY (user_id, order_id)
REFERENCES Orders (user_id, order_id) ON DELETE CASCADE,
FOREIGN KEY (coupon_id) REFERENCES Coupon_Name (coupon_id)
);

CREATE TABLE User_Curriculum_Lecture_Complete(
instructor_id CHAR(10) NOT NULL,
curriculum_name VARCHAR(50) NOT NULL,
lecture_name VARCHAR(50) NOT NULL,
user_id CHAR(10) NOT NULL,
lecture_complete BOOL DEFAULT FALSE,
FOREIGN KEY (instructor_id, curriculum_name, lecture_name)
REFERENCES Lecture (instructor_id, curriculum_name, lecture_name) ON DELETE CASCADE,
FOREIGN KEY (user_id) REFERENCES User (user_id),
PRIMARY KEY (instructor_id, curriculum_name, lecture_name, user_id, lecture_complete)
);

CREATE TABLE User_Curriculum_Lecture_Studied_Date(
instructor_id CHAR(10) NOT NULL,
curriculum_name VARCHAR(50) NOT NULL,
lecture_name VARCHAR(50) NOT NULL,
user_id CHAR(10) NOT NULL,
last_studied_date DATE,
FOREIGN KEY (instructor_id, curriculum_name, lecture_name)
REFERENCES Lecture (instructor_id, curriculum_name, lecture_name) ON DELETE CASCADE,
FOREIGN KEY (user_id) REFERENCES User (user_id),
PRIMARY KEY (instructor_id, curriculum_name, lecture_name, user_id, last_studied_date)
);

CREATE TABLE Comment(
comment_id INT(9) NOT NULL AUTO_INCREMENT,
instructor_id CHAR(10) NOT NULL,
curriculum_name VARCHAR(50) NOT NULL,
date DATE,
rate INT(5) DEFAULT 1,
content TEXT,
user_id CHAR(10) NOT NULL,
FOREIGN KEY (user_id) REFERENCES User (user_id),
PRIMARY KEY (comment_id, instructor_id, curriculum_name)
);

INSERT INTO User (user_id,  nickname, password)
VALUE ('seunghyun', 'shlee', 'seunghyunpassword'),
('sarah', 'sarahnick', 'sarahpassword'),
('sabin', 'sabina', 'sabinapassword');

INSERT INTO Coupon_Name (coupon_id, coupon_name)
VALUE ('1122334455', 'serialNumber'),
('SALECOUPON', '50%discountCoup'),
('BLACKFRI', '50%discountCoup');

INSERT INTO Coupon_Info (coupon_name, expiration_date, discount)
VALUES ('serialNumber', '2022-12-01', '30'),
('SALECOUPON', '2023-12-31', '50');

INSERT INTO Instructor (instructor_id, instructor_name, password, introduction)
VALUES ('teacher', '이승현', 'teacherpassword', '안녕하세요, 이승현입니다.'),
('professor', '전문가', 'professorpassword', '나는야 전문가!');

INSERT INTO Category (name)
VALUES ('database'), ('unity'), ('front'), ('back'), ('ai'), ('algorithm'), ('bigData');

INSERT INTO Curriculum (instructor_id, curriculum_name, price, category)
VALUES ('teacher', '게임 배우기', '100', 'unity'),
('teacher', '알고리즘 배우기', '250.50', 'algorithm'),
('professor', '백엔드 기초', '130.85', 'back');

INSERT INTO Lecture (instructor_id, curriculum_name, lecture_name, length)
VALUES ('teacher', '게임 배우기', '세션 1', '3500'),
('teacher', '게임 배우기', '세션 2', '4500'),
('teacher', '게임 배우기', '세션 3', '10000'),
('teacher', '알고리즘 배우기', 'task 0', '65'),
('teacher', '알고리즘 배우기', 'task 1', '4000'),
('professor', '백엔드 기초', 'introduction', '45'),
('professor', '백엔드 기초', 'lesson_1', '5370'),
('professor', '백엔드 기초', 'lesson_2', '37640');

INSERT INTO Orders (user_id, order_id)
VALUES ('sarah', '1'),
('sarah', '2'),
('sabin', '1'),
('sabin', '2'),
('sabin', '3');

INSERT INTO Orders_Curriculum (user_id, order_id, instructor_id, curriculum_name)
VALUES ('sarah', '1', 'professor', '백엔드 기초'),
('sarah', '2', 'teacher', '알고리즘 배우기'),
('sabin', '1', 'teacher', '게임 배우기'), 
('sabin', '2', 'teacher', '알고리즘 배우기'),
('sabin', '3', 'professor', '백엔드 기초');

INSERT INTO Orders_Coupon (user_id, order_id, coupon_id)
VALUES ('sarah', '1', '1122334455'),
('sarah', '2', 'SALECOUPON'),
('sabin', '1', '1122334455'),
('sabin', '2', 'SALECOUPON'),
('sabin', '3', 'BLACKFRI');

INSERT INTO User_Curriculum_Lecture_Studied_Date (instructor_id, curriculum_name, lecture_name, user_id, last_studied_date)
VALUES ('teacher', '게임 배우기', '세션 1', 'sabin', '2021-12-31');
INSERT INTO User_Curriculum_Lecture_Studied_Date (instructor_id, curriculum_name, lecture_name, user_id, last_studied_date)
VALUES ('teacher', '게임 배우기', '세션 2', 'sabin', '2022-01-01');
INSERT INTO User_Curriculum_Lecture_Studied_Date (instructor_id, curriculum_name, lecture_name, user_id, last_studied_date)
VALUES ('teacher', '알고리즘 배우기', 'task 0', 'sarah', '2022-09-03');
INSERT INTO User_Curriculum_Lecture_Studied_Date (instructor_id, curriculum_name, lecture_name, user_id, last_studied_date)
VALUES ('professor', '백엔드 기초', 'lesson_2', 'sabin', '2021-05-11');

INSERT INTO User_Curriculum_Lecture_Complete (instructor_id, curriculum_name, lecture_name, user_id, lecture_complete)
VALUES ('teacher', '게임 배우기', '세션 1', 'sabin', '1');
INSERT INTO User_Curriculum_Lecture_Complete (instructor_id, curriculum_name, lecture_name, user_id, lecture_complete)
VALUES ('teacher', '게임 배우기', '세션 2', 'sabin', '0');
INSERT INTO User_Curriculum_Lecture_Complete (instructor_id, curriculum_name, lecture_name, user_id, lecture_complete)
VALUES ('teacher', '알고리즘 배우기', 'task 0', 'sarah', '0');
INSERT INTO User_Curriculum_Lecture_Complete (instructor_id, curriculum_name, lecture_name, user_id, lecture_complete)
VALUES ('professor', '백엔드 기초', 'lesson_2', 'sabin', '1');

INSERT INTO Comment (comment_id, instructor_id, curriculum_name, date, rate, content, user_id)
VALUES ('1', 'teacher', '게임 배우기', '2022-05-23', '3', '그럭저럭 좋아요.', 'sabin'),
('2', 'teacher', '알고리즘 배우기', '2022-06-17', '5', '유용해요!', 'sarah'),
('3', 'teacher', '알고리즘 배우기', '2021-01-01', '1', '환불 안 해주시나요?', 'sabin');