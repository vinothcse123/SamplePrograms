SET serveroutput ON size 30000;
DECLARE
  v_errm    VARCHAR2(64);
  v_code    NUMBER;
TYPE columnNames_t
IS
  TABLE OF VARCHAR2(100);
  colNames columnNames_t;
BEGIN
  SELECT COLUMN_NAME BULK COLLECT
  INTO colNames
  FROM all_tab_columns
  WHERE TABLE_NAME LIKE UPPER('MYTABLE')
  AND COLUMN_NAME LIKE 'MYCOL'
  AND OWNER LIKE 'MYOWNER'
  ORDER BY COLUMN_ID;
EXCEPTION
WHEN OTHERS THEN
  dbms_output.PUT_LINE('Exception');
  v_code := SQLCODE;
  v_errm := SUBSTR(SQLERRM, 1, 64);
  DBMS_OUTPUT.PUT_LINE (v_code || ' ' || v_errm);
END;
/
