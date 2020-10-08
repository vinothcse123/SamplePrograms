
--H:OBJECTS

SELECT * FROM ALL_OBJECTS; 

--H:Table

select * from all_tables where  table_name LIKE '%ddd%';

select * from all_synonyms where  synonym_name LIKE UPPER('%ddd%');

select * from all_mviews where  lower(mview_name) LIKE lower('%ddd%');



--H:column

--columns of the table
select * from all_tab_columns where TABLE_NAME LIKE '%ALL_INDEX%' AND COLUMN_NAME LIKE '%STATUS%';

--constraints of table
select * from all_constraints where lower(table_name) like lower('ddd');

--column information of constraint
 select * from all_cons_columns where lower(constraint_name) like lower('dd');


--Column related characteritics
SELECT *
FROM ALL_TAB_COLUMNS
WHERE TABLE_NAME LIKE 'dd%'
AND COLUMN_NAME LIKE '%d%';

--Foriegn key details

SELECT a.table_name,
  a.column_name,
  a.constraint_name,
  c.owner,
  -- referenced pk
  c.r_owner,
  c_pk.table_name r_table_name,
  c_pk.constraint_name r_pk
FROM all_cons_columns a
JOIN all_constraints c
ON a.owner            = c.owner
AND a.constraint_name = c.constraint_name
JOIN all_constraints c_pk
ON c.r_owner            = c_pk.owner
AND c.r_constraint_name = c_pk.constraint_name
Where C.Constraint_Type = 'R'
AND A.Table_Name        like '%dd%';


--H:session

select * from v$session;


--statistics of session
select * from v$mystat;


--H:index

SELECT STATUS,IDX.* FROM all_indexes IDX WHERE TABLE_NAME LIKE '%V6%';

--H:ETC

--Refresh Materialized view

begin
-- f- fast refresh
Dbms_Snapshot.Refresh( 'dd','f'); 
End;
/
