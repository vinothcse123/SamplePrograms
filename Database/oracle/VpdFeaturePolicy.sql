


CREATE OR REPLACE FUNCTION myPolicyFunction (
 v_schema IN VARCHAR2, 
 v_objname IN VARCHAR2)

RETURN VARCHAR2 AS
additionalWherecond VARCHAR2 (200);

BEGIN
 additionalWherecond := 'MYNUMBER=300';
 RETURN (additionalWherecond);
END myPolicyFunction;
/

BEGIN
 DBMS_RLS.ADD_POLICY (
  object_schema     => '', 
  object_name       => 'V6Play',
  policy_name       => 'myPolicy', 
  policy_function   => 'myPolicyFunction',
  sec_relevant_cols => '');
END;
/


SELECT * FROM V6Play;
