declare @myName varchar(MAX);
DECLARE @myInteger INT

-- SUBSTRING
SET @myName = '12345-HAI'
SET @myName = SUBSTRING(@myName,1,5);
PRINT @myName


--Find character in particular string
SET @myName = '12345-HAI'
PRINT CHARINDEX('-',@myName)


--Casting string to integer
SET @myName='666'
SET @myInteger=CAST(@myName AS INT)
PRINT @myName



--compare two strings

IF 'hai' != 'HAI'
	PRINT 'case insensitive compare'
