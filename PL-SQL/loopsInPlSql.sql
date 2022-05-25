--###################### Simple for loop

DECLARE
  v_id NUMBER;
BEGIN
  v_id :=0;
  FOR i IN 1 .. 5
  LOOP
    dbms_output.put_line(i);
    EXIT
  WHEN v_id > 25;
  END LOOP;
END;


--###################### For loop based on data selected
--- Not sure it works, double check
FOR i IN
(SELECT PP.colName FROM tableName PP WHERE effective_date='3-Jan-2005'
)
LOOP
  DBMS_OUTPUT.PUT_LINE(i.colName);
END LOOP;
END;


--###################### Loop array

DECLARE
TYPE columnNames_t
IS
  TABLE OF VARCHAR2(100);
  colNames columnNames_t;
BEGIN
  FOR i IN 1 .. colNames.count
  LOOP
    dbms_output.put_line(colNames(i));
  END LOOP;
END;
