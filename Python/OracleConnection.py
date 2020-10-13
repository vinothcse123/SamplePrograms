import cx_Oracle

# Establish the database connection
connection = cx_Oracle.connect("connection", "connection", "connection")

# Obtain a cursor
cursor = connection.cursor()

print(connection.handle())

# Execute the query
sql = """SELECT SYSDATE FROM DUAL"""
cursor.execute(sql)

# Loop over the result set
for row in cursor:
    print(row)
