
create table V6PlayPartitionByDemo
(
MyNumber1 NUMBER,
MyNumber2 NUMBER,
MyNumber3 NUMBER,
myFloat NUMBER(10,6)
);

DROP TABLE V6PlayPartitionByDemo;
INSERT INTO V6PlayPartitionByDemo(MyNumber1,MyNumber2,MyNumber3,myFloat) VALUES(1,2,3,100);
INSERT INTO V6PlayPartitionByDemo(MyNumber1,MyNumber2,MyNumber3,myFloat) VALUES(1,2,4,100);
INSERT INTO V6PlayPartitionByDemo(MyNumber1,MyNumber2,MyNumber3,myFloat) VALUES(1,2,4,1040);
INSERT INTO V6PlayPartitionByDemo(MyNumber1,MyNumber2,MyNumber3,myFloat) VALUES(1,21,3,140);
INSERT INTO V6PlayPartitionByDemo(MyNumber1,MyNumber2,MyNumber3,myFloat) VALUES(1,22,4,150);
INSERT INTO V6PlayPartitionByDemo(MyNumber1,MyNumber2,MyNumber3,myFloat) VALUES(11,2,3,100);
INSERT INTO V6PlayPartitionByDemo(MyNumber1,MyNumber2,MyNumber3,myFloat) VALUES(11,2,4,100);
INSERT INTO V6PlayPartitionByDemo(MyNumber1,MyNumber2,MyNumber3,myFloat) VALUES(11,21,3,100);
INSERT INTO V6PlayPartitionByDemo(MyNumber1,MyNumber2,MyNumber3,myFloat) VALUES(11,22,4,100);

SELECT MYNUMBER1,MYNUMBER2,myFloat,count(distinct myFloat) OVER (PARTITION BY MYNUMBER1,MYNUMBER2) AS DistinctNanCount FROM V6PlayPartitionByDemo;
