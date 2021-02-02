#GH_MISC_3
import CythonFunctions
import cx_Oracle

# Establish the database connection
connection = cx_Oracle.connect("NRSP_V", "NRSP_V", "VALDEV03")

# Obtain a cursor
cursor = connection.cursor()

print(connection.handle)
CythonFunctions.FunctionWithArgs(connection.handle);
