SET SERVEROUTPUT ON SIZE UNLIMITED

EXECUTE IMMEDIATE v_query INTO resultOut;

DBMS_OUTPUT.PUT_LINE (v_code || ' ' || v_errm);

