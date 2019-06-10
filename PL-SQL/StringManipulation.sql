declare

myString varchar2(2000);
ArrayPosFinder varchar2(2000):='12345';
findPos NUMBER;
mySubString VARCHAR2(2000);

begin

myString := '555-HELLO';
findpos := instr(myString,'-');

mySubString := substr(myString,0,findpos-1);


dbms_output.put_line(mySubString);

-- Find str
dbms_output.put_line('instr position: '||instr(ArrayPosFinder,'1'));


--Concatenate

mySubString := 'HELLO' || 'HAI';

end;

