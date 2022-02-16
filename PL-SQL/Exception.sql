declare


v_dummy number:=1;
v_errm  VARCHAR2(64);
v_query VARCHAR2(2000);

begin

WHILE (v_dummy > 0)
LOOP
  
BEGIN
select COUNT(*)
Into v_dummy
from V6D_DUPCHECK;


Exception 
  when no_data_found then
Exit;
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
end;

