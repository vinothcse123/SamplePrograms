begin
 declare @myXml xml;
 declare @name nvarchar(100);
 declare @age INT;

SET @myXml = N'<PERSON>
    <MYPROPERTY>
        <MYNAME>VINOTH</MYNAME>
		<MYNAME>MYSECONDNAME</MYNAME>
        <MYAGE>28</MYAGE>

		<FRIEND HEIGHT="25">VINOTH FRIEND 1</FRIEND>
    </MYPROPERTY>   
</PERSON>'

/* myPropertyNode is XML type returned after calling nodes
	
XML Type methods
	nodes(xquery)
	values(xquery,sqldatatype)
*/

SELECT @name = (select myPropertyNode.value('(MYNAME)[1]', 'VARCHAR(50)')  from @myXml.nodes('PERSON/MYPROPERTY') as PERSONXML(myPropertyNode));
PRINT @name

SELECT @name = (select myPropertyNode.value('(MYNAME)[2]', 'VARCHAR(50)')  from @myXml.nodes('PERSON/MYPROPERTY') as PERSONXML(myPropertyNode));
PRINT @name

SELECT @name = (select myFriendNode.value('@HEIGHT', 'VARCHAR(50)')  from @myXml.nodes('PERSON/MYPROPERTY/FRIEND') as PERSONXML(myFriendNode));
PRINT @name

end;
