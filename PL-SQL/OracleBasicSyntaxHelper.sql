DECLARE

vnumber number;
vstring varchar(30) := 'V6P_DE5';


vdirectinitNumber number :=10;
vincrementer number :=1;
vconcatstring varchar(30);



BEGIN
  
vnumber := 123;
vincrementer := vincrementer+8;
vconcatstring  := 'V6P_DE'|| to_char(vincrementer);

INSERT INTO performdbo.dqm_overrides VALUES('V6P_DE4',vnumber,100,getdate(),getdate(),1,'','P','VINO',getdate(),'d');

vnumber := vnumber + 1;
INSERT INTO performdbo.dqm_overrides VALUES(vconcatstring,vnumber,100,getdate(),getdate(),1,'','P','VINO',getdate(),'d');



INSERT INTO performdbo.dqm_overrides VALUES(vstring,vdirectinitNumber,100,getdate(),getdate(),1,'','P','VINO',getdate(),'d');

commit;

SELECT 'Value' = @vnumber
END;


