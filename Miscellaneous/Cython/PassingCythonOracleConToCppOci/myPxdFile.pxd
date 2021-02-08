from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp.memory cimport unique_ptr
from libc.stdint cimport *
from libcpp cimport bool

cimport cython

cdef extern from "CppFile.cpp":
    void sameFunctionNameinBoth()

cdef extern from "CppFile.cpp":
    void FunctionWithArgs(long long int id)

cdef extern from "CppFile.cpp":
    void FunctionWithVector(vector[int] myVec)

#fused type - Support for templates
ctypedef fused genericFusedType:
    cython.int
    cython.double
    cython.p_char

cdef extern from "CppFile.cpp":
    void FunctionWithUniquePtr(unique_ptr[int] &myuniquePtr)
    void initUniquePtr(unique_ptr[int] &myuniquePtr)
    bool returnBooleanValue()

    cdef enum MyEnum:
        MyEnumValue1 "MyEnum::MyEnumValue1"

    void myFunctionTakingEnumClass(MyEnum myEnumObj)

    void myTemplateFunction[T](T a)
    

    cdef cppclass MyCppClass:
        int myInt
        string myString
        MyEnum myEnumObj

        #cppclass MyInnerClass:
            #MyInnerClass()
            #int myInnerInt

    bool myFunctionTakingClass(MyCppClass obj)
    
    cdef cppclass MyTemplateClass[T]:
        pass

    ctypedef MyTemplateClass[int64_t] Int64

    void throwException() except +

    void myFuncTakingConst(const int a)


