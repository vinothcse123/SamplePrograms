$ORACLE_HOME/bin/sqlldr userid=${DB_CONNECTION_STRING} control=v6Play.ctl    direct=y errors=0 skip=0

v6Play.ctl
LOAD DATA
INFILE 'v6Play.dat'
APPEND
INTO TABLE MYSCHEMA.V6Play
fields terminated by ","
(
MyNumber  ,
myTimeStamp  DATE "dd-mon-yyyy"  ,
MyNumber2  
)


v6Play.dat
10,31-JAN-2008,10000


