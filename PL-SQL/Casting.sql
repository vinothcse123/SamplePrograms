declare

myInp varchar2(2000);
myInt number;

begin
myInp := '55';

begin
myInt := cast(myInp as number);
exception
  when others then
  dbms_output.put_line('EXCEPTION');
    myInt:=0;
end;

dbms_output.put_line(myInt);

end;

