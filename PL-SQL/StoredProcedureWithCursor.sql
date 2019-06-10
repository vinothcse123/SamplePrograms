

CREATE TABLE V6Table
(
MyId NUMBER,
MYSTRING VARCHAR2(200)
);


INSERT INTO V6Table VALUES(10,'VINOTH');
INSERT INTO V6Table VALUES(20,'SARAVANAN');


create package V6DelPkg as 
  type cursvar is ref cursor return V6Table%ROWTYPE;
end myProcPkg;

create or replace procedure V6DelProcCursor(myDept in number,
                        myCursor in out V6DelPkg.cursvar
                        ) as
begin
    open myCursor for select * from V6Table;

end V6DelProcCursor;



DECLARE 
  v_cur SYS_REFCURSOR;
  v_a  NUMBER;
    v_b  VARCHAR(100);
BEGIN
  V6DelProcCursor(10,v_cur);

  LOOP
    FETCH v_cur INTO v_a,v_b;
    EXIT WHEN v_cur%NOTFOUND;
    dbms_output.put_line(v_a );
  END LOOP;
  CLOSE v_cur;
END;