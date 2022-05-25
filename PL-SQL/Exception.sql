DECLARE
  v_dummy NUMBER:=1;
  v_errm  VARCHAR2(64);
  v_query VARCHAR2(2000);
BEGIN
  WHILE (v_dummy > 0)
  LOOP
    BEGIN
      SELECT COUNT(*) INTO v_dummy FROM V6D_DUPCHECK;
    EXCEPTION
    WHEN no_data_found THEN
      EXIT;
    END;
    dbms_output.put_line('EQUAL');
  END LOOP;
EXCEPTION
WHEN OTHERS THEN
  DBMS_OUTPUT.PUT_LINE('Exception raised');
  v_code := SQLCODE;
  v_errm := SUBSTR(SQLERRM, 1, 64);
  DBMS_OUTPUT.PUT_LINE (v_code || ' ' || v_errm);
  NULL;
END;
