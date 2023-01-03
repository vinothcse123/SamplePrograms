
--H:OBJECTS

SELECT * FROM ALL_OBJECTS WHERE UPPER(OBJECT_NAME) LIKE UPPER('%VRG_VINOTH_PRO%'); 

--Package to get table definition
select dbms_metadata.get_ddl('TABLE', upper('TABLE_NAME_IN_CAPS')) from user_tables;

describe schemaName.tableName;


--H:Database

select * from VRG_output_VINOTH_cps@VINOKSL4;
select * from VRG_output_VINOTH_cps@VINOKSL4;

SELECT * FROM DBA_DB_LINKS WHERE DB_LINK LIKE 'R_VINOTH_%';

SELECT * FROM ALL_DB_LINKS WHERE DB_LINK LIKE 'R%';

SELECT * FROM USER_DB_LINKS WHERE DB_LINK LIKE 'R_VINOTH_%';

--H:Table

select * from all_tables where  table_name LIKE '%ddd%';

select * from all_synonyms where  synonym_name LIKE UPPER('%VRG_VINOTH_PRO%');

select * from all_mviews where  lower(mview_name) LIKE lower('%VRG_VINOTH_PRO%');  

select * from all_views where  lower(view_name) LIKE lower('%ALL_INDEXES%');  

select * from ALL_PART_TABLES where table_name = 't1';

select * from ALL_tab_subpartitions where table_name = 't1';

--table size
select bytes/1024/1024 MB,T.* from DBA_segments T where segment_name LIKE UPPER('VRG_AGGREGATED_DATA%') AND OWNER LIKE 'VINO_P_1017572';

--H:column

--columns of the table
select * from all_tab_columns where TABLE_NAME LIKE UPPER('%TRDS_VINOTHORY_DATA_SCOPE%') AND COLUMN_NAME LIKE '%%' AND OWNER LIKE '%%' ORDER BY COLUMN_ID;

--constraints of table
select * from all_constraints where lower(table_name) like lower('all_indexes');


--H:constraints

--column information of constraint
 select * from all_cons_columns where lower(constraint_name) like lower('AVCON_34567_67891');

ALTER TABLE VRG_AGG_TABLE_KEY DISABLE CONSTRAINT AGC_AGT_ID_FK;


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
AND A.Table_Name        like '%%';


--H:Procedure

select * from all_source where name LIKE UPPER('%%') order by type, line;


--H:DBA
--:session
--connection
--Dynamic performance views(v$)

SELECT * FROM v$version;


alter session set current_schema = VINO_P_1017572; 

-- Number of active connections

select count(*) from v$session;


-- Number of active connections allowed 
SELECT name, value 
  FROM v$parameter
 WHERE name = 'sessions';



-- For the given user, select value in column PROFILE,
SELECT * FROM dba_users WHERE USERNAME LIKE 'VINO_P_1121382%' AND PROFILE <> 'DEFALT';

-- For connection timeout, resource name is IDLE_TIME
select * from DBA_PROFILES where PROFILE LIKE 'DEFAU%';

--statistics of current session
select * from v$mystat where statistic# = 52;

--List of all statistics
select * from V$STATNAME where lower(name) like '%physical%';

select * from V$SESSTAT;

select * from V$SYSSTAT;


--H:index

SELECT STATUS,IDX.* FROM all_indexes IDX WHERE TABLE_NAME LIKE UPPER('%') AND TABLE_OWNER LIKE 'VINO_P_503412';

SELECT IDX.* FROM all_ind_columns IDX WHERE INDEX_NAME LIKE 'ARS_VRG_INDX01' AND TABLE_OWNER LIKE 'VINO_P_503412%';

SELECT STATUS,T.* FROM DBA_IND_PARTITIONS T WHERE INDEX_NAME LIKE 'AGD_MAH_BM_I' AND INDEX_OWNER LIKE 'VINO_P_1157731'; 

ANALYZE INDEX AGD_MAH_BM_I COMPUTE STATISTICS;

alter session set skip_unusable_indexes = true;

alter index indexName rebuild;

--H:ETC

--Refresh Materialized view mview

begin
-- f- fast refresh
Dbms_Snapshot.Refresh( 'mrds_Fctset_VINOTH','f'); 
End;
/

--Recently executed Query
select sysdate,v.LAST_ACTIVE_TIME,
          v.FIRST_LOAD_TIME,
            v.SQL_TEXT,
           v.PARSING_SCHEMA_NAME,
           v.DISK_READS,
           v.ROWS_PROCESSED,
           v.ELAPSED_TIME,
           v.service,
           v.*
      from v$sql v
      WHERE V.SERVICE='VINODEVL1' and PARSING_SCHEMA_NAME <> 'SYS'
      ORDER BY V.LAST_ACTIVE_TIME  DESC;


--H:PRIVILEGE

SELECT * FROM DBA_SYS_PRIVS WHERE PRIVILEGE LIKE '%CONTEXT%';


--H:policy

select object_owner, policy_name,object_name as policy_applied_on, pf_owner, package, function
from dba_policies
where object_owner like 'ddd%';


--H:Package

--Retrive package body
SELECT TEXT
    FROM all_source
   WHERE TYPE = 'PACKAGE BODY' AND name LIKE UPPER('%%')
ORDER BY line;


--H:Explain plan
--H:Execution plan


explain plan for select * from dual;

select * from table(dbms_xplan.display);


