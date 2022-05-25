declare

-- Array
TYPE namearray_t IS VARRAY(5) OF VARCHAR2(10); 
Type grades_t IS VARRAY(5) OF INTEGER;
names namearray_t;

-- Table

TYPE columnNames_t IS TABLE OF VARCHAR2(100); 
colNames columnNames_t;

begin

DBMS_OUTPUT.PUT_LINE('Hello PL/SQL !!!');

end;
