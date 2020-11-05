from myPxdFile cimport sameFunctionNameinBoth as c_sameFunctionNameinBoth 
from myPxdFile cimport unlockConditionVariable as c_unlockConditionVariable
from myPxdFile cimport makeWaitWithCondVariable as c_makeWaitWithCondVariable

from myPxdFile cimport FunctionWithArgs as c_FunctionWithArgs
from myPxdFile cimport FunctionWithVector as c_FunctionWithVector
from myPxdFile cimport FunctionWithUniquePtr as c_FunctionWithUniquePtr
from myPxdFile cimport myFunctionTakingEnumClass as c_myFunctionTakingEnumClass
from myPxdFile cimport MyEnum
from myPxdFile cimport MyEnumValue1
from myPxdFile cimport genericFusedType
from myPxdFile cimport myTemplateFunction
from myPxdFile cimport myFunctionTakingClass as c_myFunctionTakingClass
from myPxdFile cimport returnBooleanValue as c_returnBooleanValue
from myPxdFile cimport MyCppClass
from myPxdFile cimport throwException
cimport myPxdFile as cppmyPxdFile
from myPxdFile cimport myFuncTakingConst

from libcpp.memory cimport unique_ptr
from cython.operator cimport dereference as deref

def directPythonFunc():
    print('Calling python function in cython module')

cdef extern from "CppFile.cpp":
    void myCFunction()

def pythonCallingCFunc():
    myCFunction();

def sameFunctionNameinBoth():
    c_sameFunctionNameinBoth();

def FunctionWithArgs(myId):
    c_FunctionWithArgs(myId);

def FunctionWithVector(myId):
    c_FunctionWithVector(myId);


cdef class MyExtensiveClass:
    cdef public int myInt 
    cdef  unique_ptr[int] myUniqPtr     
    
    

    def __init__(self):
        self.myInt = 1009

    myPythonVar = 1030

    cdef void myCdefFunc(self):
        cdef  unique_ptr[MyCppClass] myUniqPtrMyCppClass
        myUniqPtrMyCppClass.reset(new MyCppClass())

        #cdef  unique_ptr[MyCppClass.MyInnerClass] myUniqPtrMyInnerClass
        #myUniqPtrMyInnerClass.reset(new MyCppClass.MyInnerClass())

    def MyExtensiveClass(self):
        #myCdefFunc() - Use non class function to use this functionality
        pass

    def derefencePointer(self,MyExtensiveClass2 otherObject):
        deref(otherObject.myUniqPtr2)


cdef class MyExtensiveClass2:
    cdef  unique_ptr[int] myUniqPtr2


def returnPythonClass():
    myObj = MyExtensiveClass()
    print(myObj.myInt)
    return myObj

#Note :  MyExtensiveClassObj is declared with type. This is called type declaration. This is done so because using python object, we are referring the c type myUniqPtr

def takePythonObjectAndAccessCType(MyExtensiveClass MyExtensiveClassObj):
    print(MyExtensiveClassObj.myPythonVar)
    print(MyExtensiveClassObj.myInt)
    c_FunctionWithUniquePtr(MyExtensiveClassObj.myUniqPtr)

class MyPythonEnum:
    MyPythonEnumValue1 = 200
    MyPythonEnumValue2 = 201


def convertToCppEnum(myPythonEnumObject):
    cdef MyEnum myEnumObj
    if myPythonEnumObject == MyPythonEnum.MyPythonEnumValue1:
        myEnumObj=MyEnumValue1
    c_myFunctionTakingEnumClass(myEnumObj)
    pass
 
def myGenericFuncion(genericFusedType fusedTypeObj):
    myTemplateFunction(fusedTypeObj)

def LoopingAllElementsInList(listObj):
    cdef int a
    for x in listObj:
        a=x
        print(a);

cdef returnCType():
    cdef int a
    return a

cdef class MyTestClasss:
    cdef int myEnumObj 

cdef returnCTypeEnum():
    cdef MyTestClasss mydd    
    return MyTestClasss

#Work in progress
def passingTupleToCppProgram():
    #cdef tuple[int,int] myTuple
    pass




def passingCppClassToCppProgram(nodeId,myListofList):  
    cdef MyCppClass obj
    for curTuple in myListofList:        
        obj.myInt=1003
        obj.myString=curTuple[1]
        obj.myEnumObj=MyEnumValue1
        c_myFunctionTakingClass(obj)
    
def myFunc(a):
    return a

cdef class PyColumnType:
    cdef public:
        int eBOOL
        int eINTEGER32
        int eINTEGER64
        int eFLOAT
        int eDOUBLE
        int eSTRING
        int eDATE
        int eBLOB
    def __cinit__(self):
        eBOOL = 0
        eINTEGER32 = 1
        eINTEGER64 = 2
        eFLOAT = 3
        eDOUBLE = 4
        eSTRING = 5
        eDATE = 6
        eBLOB = 7

cdef testingMapCPP(obj):
    result = {
    PyColumnType.eBOOL:  myFunc(100),
    PyColumnType.eINTEGER64:  myFunc(200),
    }
    print(result.get(obj,"asdf"))

def testingMap(obj):
    testingMapCPP(obj)

#This cannot be called from python client
cdef myCdefFuncion():
    cdef int a    
    print("myCdefFuncion is called %d" %a)

@staticmethod
cdef myCdefStaticFuncion():
    cdef int a    
    print("myCdefFuncion is called %d" %a)

#This cannot be called from python client
def defFuncUsingInt():
    cdef int *a
    #a=malloc()
    #print("defFuncUsingInt is called %d" %a)
    myCdefStaticFuncion()

def returnBooleanValue():
    return c_returnBooleanValue()


def pythrowException():
    throwException()

def pymyFuncTakingConst(a):
    myFuncTakingConst(a)

def makeWaitWithCondVariable():
    with nogil:
        c_makeWaitWithCondVariable()

def unlockConditionVariable():
    with nogil:
        c_unlockConditionVariable()
