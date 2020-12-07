-- partioned index

-- LOCAL :  It creates partition index on table with partition info provided while creating table
CREATE INDEX V6PlayPartition_idx ON V6PlayPartition(MyNumber) LOCAL;
