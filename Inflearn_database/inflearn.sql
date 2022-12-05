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
