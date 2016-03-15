declare

cursor v_cursor is select id from employee_profile where msisdn like '666555%';
v_id varchar(20);

begin

open v_cursor;

loop

fetch v_cursor into v_id;

dbms_output.put_line(v_id);

exit when v_cursor%notfound;

end loop;


end;
