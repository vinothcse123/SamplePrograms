
#include<iostream>
#include<string>
#include<tuple>
using namespace std;

#include <iostream>
#include "dpi.h"
#include <cstring>
#include <string>

#define MAJOR_VERSION 4
#define MINOR_VERSION 1

using std::string;

dpiContext *pContextBefore = NULL;
dpiContext *pContext = NULL;
dpiConn *conn;
dpiConn *connBefore;


int dpiSamples_showError(void)
{
    dpiErrorInfo info;

    dpiContext_getError(pContext, &info);
    fprintf(stderr, "ERROR: %.*s (%s: %s), offset: %u\n", info.messageLength,
            info.message, info.fnName, info.action, info.offset);
    return -1;
}

void connectToDb(long long int handleId)
{
    dpiErrorInfo errorInfo;


        dpiConnCreateParams createParams;

            if (dpiContext_createWithParams(MAJOR_VERSION, MINOR_VERSION,
                                    NULL, &pContext, &errorInfo) < 0)
    {
        fprintf(stderr, "ERROR: %.*s (%s : %s)\n", errorInfo.messageLength,
                errorInfo.message, errorInfo.fnName, errorInfo.action);
    }


     if (dpiContext_initConnCreateParams(pContext, &createParams) < 0)
        return;

    createParams.externalHandle = (void *)handleId;
     
    if (dpiConn_create(pContext, NULL,
                       0, NULL,
                       0, NULL,
                       0, NULL, &createParams, &conn) < 0)
    {
        dpiErrorInfo info;
        dpiContext_getError(pContext, &info);
        fprintf(stderr, "ERROR: %.*s (%s: %s), offset: %u\n", info.messageLength,
                info.message, info.fnName, info.action, info.offset);
    }

}

int fetch(long long int handleId)
{
    dpiStmt *stmt;
    int found;
    dpiNativeTypeNum nativeTypeNum;
    dpiData *intColValue;
    dpiData *strColValue;
    uint32_t numQueryColumns, bufferRowIndex, i, rowidAsStringLength;
    string query = "SELECT MyNumber,MyVarchar FROM V6PlayPartition";
    if (dpiConn_prepareStmt(conn, 0, query.c_str(), query.length(), NULL, 0,
                            &stmt) < 0)
        return dpiSamples_showError();

    if (dpiStmt_execute(stmt, 0, &numQueryColumns) < 0)
        return dpiSamples_showError();

    while (true)
    {
        if (dpiStmt_fetch(stmt, &found, &bufferRowIndex) < 0)
            return dpiSamples_showError();

        if (!found)
            break;

        if (dpiStmt_getQueryValue(stmt, 1, &nativeTypeNum, &intColValue) < 0)
            return dpiSamples_showError();

        if (dpiStmt_getQueryValue(stmt, 2, &nativeTypeNum, &strColValue) < 0)
            return dpiSamples_showError();

        printf("\n%lld %.*s\n", intColValue->value.asInt64, strColValue->value.asBytes.length, strColValue->value.asBytes.ptr);
    }
}


static void myCFunction()
{
    //std::cout << "Hello, My C++ is called from python !!!" << std::endl;
    printf("My C function is called from python! Superb\n");
}


static void sameFunctionNameinBoth()
{
    //std::cout << "Hello, My C++ is called from python !!!" << std::endl;
    printf("My testPxd function is called from python! Nice\n");
}


static void FunctionWithArgs(long long int id)
{
    std::cout << "int received from python is "<<  id<< std::endl;   

    connectToDb(id);
    fetch(id);

}


static void FunctionWithVector(std::vector<int> myVec)
{
    std::cout << "Vector is received Second element is "<<  myVec[1]<< std::endl;   
}

static void initUniquePtr(std::unique_ptr<int> &myUPtr)
{
    std::cout << "unique_ptr is set  "<<  1<< std::endl;   
    *myUPtr =6666;
}
static void FunctionWithUniquePtr(std::unique_ptr<int> &myUPtr)
{
    std::cout << "unique_ptr is received "<<  1<< std::endl;   
}

enum class MyEnum
{
    MyEnumValue1=200,
    MyEnumValue2
};

class MyCppClass
{
    public:
    int myInt=100;
    string myString;
    MyEnum myEnumObj;

    class MyInnerClass
    {
        public:
        MyInnerClass();   
    int myInnerInt=100;
    };
};


void myFunctionTakingEnumClass(MyEnum myEnumObj)
{
    std::cout << "Enum received "<<  (int)myEnumObj<< std::endl;
}

template<typename T>
void myTemplateFunction(T a)
{
    std::cout << "myTemplateFunction "<<  a<< std::endl;
}

void functionTakingTuple(tuple<int,int> a)
{
    std::cout << "functionTakingTuple "<< 1<< std::endl;
}

bool myFunctionTakingClass(MyCppClass obj)
{
    std::cout << "myFunctionTakingClass - int"<< obj.myInt<< std::endl;
        std::cout << "myFunctionTakingClass -string "<< obj.myString<< std::endl;
        std::cout << "myFunctionTakingClass -Enum "<< (int)obj.myEnumObj<< std::endl;


}

bool returnBooleanValue()
{
    return true;
}

template<typename T>
class MyTemplateClass
{
    T a;
};

struct MyException : public exception {
   const char * what () const throw () {
      return "C++ Exception";
   }
};
 

void throwException()
{
    throw MyException();
}


void myFuncTakingConst(const int a)
{
    std::cout << "myFuncTakingConst "<<  a<< std::endl;
}

