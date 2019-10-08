$ORACLE_HOME/bin/sqlldr userid=${DB_CONNECTION_STRING} control=v6Play.ctl    direct=y errors=0 skip=1

v6Play.ctl
LOAD DATA
INFILE 'v6Play.dat'
APPEND
INTO TABLE MYSCHEMA .V6Play
fields terminated by ","
(
MyNumber  ,
myTimeStamp  DATE "yyyy-mm-dd hh24::mi:ss"  ,
MyNumber2  
)


v6Play.dat
A,B,C
1440,2019-10-03 15:47:00,10000


