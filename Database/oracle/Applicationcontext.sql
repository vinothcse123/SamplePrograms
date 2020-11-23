

/* Context creation */
CREATE OR REPLACE PACKAGE MY_PACKAGE IS
PROCEDURE setctx (policy_group VARCHAR2);
END;

CREATE OR REPLACE PACKAGE BODY MY_PACKAGE AS
PROCEDURE setctx ( policy_group varchar2 ) IS
BEGIN


DBMS_SESSION.SET_CONTEXT('MYCONTEXT','MY_KEY', policy_group);
END;
END;

grant create any context to NRSP_V;


CREATE OR REPLACE CONTEXT MYCONTEXTD using MY_PACKAGE;

select * from dba_context;
