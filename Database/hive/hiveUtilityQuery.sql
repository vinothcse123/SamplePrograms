

--------------------------------------H:Table



--Table Property scripts

describe FORMATTED myDatabase.myTable;

--Show Table Schema
SHOW CREATE TABLE myDatabase.myTable;

show partitions myDatabase.myTable;

show table extended LIKE `myDatabase.myTable` partition (dwh_dd_id=1000,dwh_cddch_id='eee');

MSCK REPAIR TABLE myDatabase.myTable;

show tables in myDatabase;


--Partition related

ALTER TABLE myDatabase.myTable
ADD PARTITION (ded=1000);

show partitions myDatabase.myTable;

--------------------------------------H:Database

show SCHEMAS LIKE '*333*';



