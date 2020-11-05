import CythonFunctions
from  CythonFunctions import *
import threading
import os
import time
import sys

CythonFunctions.directPythonFunc();
CythonFunctions.pythonCallingCFunc();
CythonFunctions.sameFunctionNameinBoth();
CythonFunctions.FunctionWithArgs("IamFromPython");
CythonFunctions.FunctionWithVector([10,20]);


#Accessing C types in python
myPythonObject = CythonFunctions.returnPythonClass()
print(myPythonObject.myPythonVar)
print(myPythonObject.myInt)
CythonFunctions.takePythonObjectAndAccessCType(myPythonObject)

CythonFunctions.convertToCppEnum(CythonFunctions.MyPythonEnum.MyPythonEnumValue1)

CythonFunctions.myGenericFuncion(100)
CythonFunctions.myGenericFuncion(89.0002)
CythonFunctions.myGenericFuncion("myString")


CythonFunctions.LoopingAllElementsInList([98,86])

CythonFunctions.passingCppClassToCppProgram(100,[["newString","two"]])
CythonFunctions.testingMap(CythonFunctions.PyColumnType.eBOOL)

#CythonFunctions.myCdefFuncion() Cannot be called
CythonFunctions.defFuncUsingInt()

print(CythonFunctions.returnBooleanValue())


try:
    CythonFunctions.pythrowException()
except RuntimeError as e:
    print(e)



#Conditional variable test
def threadFunc(id):
    print("producerThread")
    #makeWaitWithCondVariable()



producerThread = threading.Thread(target=threadFunc, args=(10,))
producerThread.start()
print("Main thread continues job after starting thread...")
#unlockConditionVariable()
