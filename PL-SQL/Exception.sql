declare


v_dummy number:=1;

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
NULL;
end;

