for i in (select PP.POSITION_ID  from HOLDINGDBO.POSITION PP where entity_id like 'NQNEWI01' and effective_date='3-Jan-2005')
loop
  DBMS_OUTPUT.PUT_LINE(i.position_id);
  end loop;
end;
