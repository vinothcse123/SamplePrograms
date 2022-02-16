declare

v_numberOutput number;
v_datevariable date;


--Temporary procedure not stored

procedure temporaryProcedure(
numberInput in number,
doubleInput in number,
stringInput in VARCHAR2,
dateInput in date,
numberoutput OUT number
)
is
v_localVariable number;
begin
numberoutput := 100;
end temporaryProcedure;


--Anonymous Block begin
begin
temporaryProcedure(
numberInput=> 9,
doubleInput=>88.08,
stringInput=>'HAI',
dateInput=>v_datevariable,
numberoutput=>v_numberOutput
);
end;
