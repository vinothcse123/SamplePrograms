
--Global Temporary table

-- Temporary table will not be dropped at end of session, where as data inserted in one session is not visible to others.
CREATE GLOBAL TEMPORARY TABLE V6Play(myNumber NUMBER)
ON COMMIT PRESERVE ROWS; -- While commiting data will be saved to temporary table

CREATE GLOBAL TEMPORARY TABLE V6Play(myNumber NUMBER)
ON COMMIT DELETE  ROWS; -- While commiting data will be deleted from temporary table
