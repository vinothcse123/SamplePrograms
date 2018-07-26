
DECLARE
@vEntityId VARCHAR(MAX)
BEGIN
SET @vEntityId='V6_ENT'
SELECT @vEntityId=ENTITY_ID FROM RULES.DBO.ENTITY WHERE ENTITY_ID='V6C_EN1';
PRINT @vEntityId
END

-- CURSOR

DECLARE @MyCursor CURSOR;
DECLARE @MyField VARCHAR(MAX);
BEGIN
    SET @MyCursor = CURSOR FOR
    select  ENTITY_ID from RULES.dbo.ENTITY
        where ENTITY_ID LIKE 'V6C_EN%'      

    OPEN @MyCursor 
    FETCH NEXT FROM @MyCursor 
    INTO @MyField

    WHILE @@FETCH_STATUS = 0
    BEGIN
      PRINT @MyField
      FETCH NEXT FROM @MyCursor 
      INTO @MyField 
    END; 

    CLOSE @MyCursor ;
    DEALLOCATE @MyCursor;
END;



-- Function


