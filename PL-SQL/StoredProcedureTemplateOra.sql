create or replace procedure V6DelProcSimple(myDept in number,
                        MyOut out number
                        ) as
begin
         MyOut := 221;
end V6DelProcSimple;




declare
myOut number;
begin
  V6DelProcSimple(5,myOut);
  dbms_output.put_line(myOut);  
  end;
