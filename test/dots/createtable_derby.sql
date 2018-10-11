connect 'jdbc:derby:/mnt/dots/TESTDB;user=u1;password=p1';
create schema u1;
drop table BASIC1;
drop table BASIC2;
drop table BASIC3;
drop table BASIC4;
drop table BASIC5;
drop table BASIC6;
drop table BID;
drop table ITEM;
drop table REGISTRY;
CREATE TABLE BASIC1 (ID_1 CHAR(15) NOT NULL, RND_CHAR VARCHAR(50), RND_FLOAT FLOAT, PRIMARY KEY (ID_1));
CREATE TABLE BASIC2 (ID_2 CHAR(15) NOT NULL, RND_INTEGER INTEGER, RND_TIME TIME, RND_DATE DATE, PRIMARY KEY (ID_2));
CREATE TABLE BASIC3 (ID_1 CHAR(15) NOT NULL, ID_2 CHAR(15) NOT NULL, RND_TIMESTAMP TIMESTAMP, RND_INT INTEGER, PRIMARY KEY (ID_1, ID_2));
CREATE TABLE BASIC4 (ID_4 CHAR(15) NOT NULL, NAME VARCHAR(30), AGE INTEGER, SALARY FLOAT, HIREDATE DATE, DEPTNO INTEGER, PRIMARY KEY(ID_4));
CREATE TABLE BASIC5 (ID_5 CHAR(15) NOT NULL, NAME VARCHAR(30), AGE INTEGER, SALARY FLOAT, DOC CLOB(1000),  PRIMARY KEY (ID_5));
CREATE TABLE BASIC6 (ID_6 CHAR(15) NOT NULL, NAME VARCHAR(30), AGE INTEGER, SALARY FLOAT, PHOTO BLOB(1000), PRIMARY KEY (ID_6));
CREATE TABLE REGISTRY (USERID CHAR(15) NOT NULL,PASSWD CHAR(10),ADDRESS CHAR(200),EMAIL CHAR(40),PHONE CHAR(15),PRIMARY KEY (USERID));
CREATE TABLE ITEM (ITEMID CHAR(15) NOT NULL,SELLERID CHAR(15) NOT NULL,DESCRIPTION VARCHAR(500),BID_PRICE FLOAT,START_TIME DATE,END_TIME DATE,BID_COUNT INTEGER,PRIMARY KEY (ITEMID));
CREATE TABLE BID (ITEMID CHAR(15) NOT NULL,BIDERID CHAR(15) NOT NULL,BID_PRICE FLOAT,BID_TIME DATE,FOREIGN KEY (ITEMID) REFERENCES ITEM (ITEMID));
exit;

