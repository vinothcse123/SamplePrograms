
declare

v_stringVar varchar2(2000);



--Anonymous Block begin
begin

v_stringVar := 'HAI';
v_stringVar := v_stringVar || 'HELLO';
v_stringVar := v_stringVar || ' ''ADDED APOSTROPHE ';

end;
