--H:Index

create unique index V6PlayUniqueIdx ON V6Play(MyNumber);

--rebuild the index
ALTER INDEX V6PlayUniqueIdx REBUILD;

-- make index as UNUSABLE - STATUS COLUMN IN all_index, To enable again, rebuild index
alter index V6PlayUniqueIdx unusable;

--Instructing to skip unusable index


-- partioned index

-- LOCAL :  It creates partition index on table with partition info provided while creating table
CREATE INDEX V6PlayPartition_idx ON V6PlayPartition(MyNumber) LOCAL;
