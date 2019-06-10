declare

myXml xmltype;
myAge varchar2(2000);


begin
myXml := xmltype.createxml('<PERSON>
    <MYPROPERTY>
        <MYNAME>VINOTH</MYNAME>
    <MYNAME>MYSECONDNAME</MYNAME>
        <MYAGE>28</MYAGE>

    <FRIEND HEIGHT="25">VINOTH FRIEND 1</FRIEND>
    </MYPROPERTY>   
</PERSON>');

SELECT EXTRACTVALUE(myXml,'/PERSON/MYPROPERTY/MYAGE/text()') INTO myAge from dual;

dbms_output.put_line(myAge);

end;

