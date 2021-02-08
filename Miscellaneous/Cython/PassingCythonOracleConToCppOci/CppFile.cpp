
#include<iostream>
#include<string>
#include<tuple>
using namespace std;

#include <iostream>
#include <cstring>
#include <string>
#include <iostream>
#include <oci.h>
#include <string>
#include <cstring>

using namespace std;


using std::string;


class OCIConnection
{
public:
    //V6P
    OCIEnv *pOciEnv;
    OCIError *pOciErrorHandle;
    OCISvcCtx *pOciServiceContextHandle = nullptr;
    sword ociret; /* return code from OCI calls */
    ub2 id_col;
    OCIServer *pOciServerHandle = nullptr;
    OCISession *pOciSessionHandle = nullptr;

    int connectToDb(long long int handleId);
    int insertToTable();
};

void handleError(OCIError *pOciErrorHandle)
{
    sb4 errcode = 0;
    text errorBuf[5120];
    sword errorCode = OCIErrorGet((dvoid *)pOciErrorHandle, (ub4)1, (text *)NULL, &errcode, errorBuf, (ub4)sizeof(errorBuf), OCI_HTYPE_ERROR);

    if (OCI_ERROR != errorCode)
        std::cout << " \n==============OCI ERROR: " << errcode << " : " << (const char *)errorBuf << std::endl;
    else
        std::cout << " \n==============Error in getting OCI ERROR: " << errorCode << (const char *)errorBuf << std::endl;

    exit(-1);
}

void IS_ERROR(OCIError *pOciErrorHandle, sword errorCode)
{

    if (errorCode != OCI_SUCCESS)
    {
        std::cout << " \n==============Returned error Code: " << errorCode << std::endl;
        if (errorCode == OCI_ERROR)
            handleError(pOciErrorHandle);
    }
}

int OCIConnection::connectToDb(long long int handleId)
{

    //Create Environment

    OCIEnv *pOciEnvTemp;
    OCIError *pOciErrorHandleTemp;
        std::cout << " \n==============V6P: TEXT_AND_VALUE "<<  1  << "==================" << std::endl;

	if (OCIEnvNlsCreate((OCIEnv **)&pOciEnvTemp, (ub4)OCI_DEFAULT,
					 (dvoid *)0, (dvoid * (*)(dvoid *, size_t))0,
					 (dvoid * (*)(dvoid *, dvoid *, size_t))0,
					 (void (*)(dvoid *, dvoid *))0, (size_t)0, (dvoid **)0,0,0))
	{
		std::cout << " \n==============V6P: Unabled to create Environment==================" << std::endl;
		return -1;
	}

	// Set error handler

	IS_ERROR(pOciErrorHandleTemp, OCIHandleAlloc((dvoid *)pOciEnvTemp, (dvoid **)&pOciErrorHandleTemp, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0));


    pOciServiceContextHandle = (OCISvcCtx*) handleId;

    //Get environment handle from service context handle
    IS_ERROR(pOciErrorHandleTemp, OCIAttrGet((dvoid *)pOciServiceContextHandle, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)&pOciEnv, (ub4)0, (ub4)OCI_ATTR_ENV, (OCIError *)pOciErrorHandleTemp));

    //Release temporary handles
    IS_ERROR(pOciErrorHandleTemp, OCIHandleFree((dvoid *)pOciEnvTemp,OCI_HTYPE_ENV));

    // Set error handler

	IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciErrorHandle, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0));
    //pOciErrorHandle=pOciErrorHandleTemp;

    return 0;
}

int OCIConnection::insertToTable()
{
        std::cout << " \n==============V6P: TEXT_AND_VALUE "<<  1  << "==================" << std::endl;

    const int ROW_COUNT = 5;
    OCIStmt *stmthp = (OCIStmt *)0;
    OCIBind *ociBind = (OCIBind *)0;

    sb2 indicatorForColumn1[ROW_COUNT]={-1,0,0}; /* indicators - passing value as -1, inserts null for row*/  
    ub2 LegthForColumn1[ROW_COUNT]={3};       /* return lengths */
    ub2 returnCodeForColumn1[ROW_COUNT]={0};  /* return codes */

    char strBuffer[ROW_COUNT][100] = {};
    int intBuffer[ROW_COUNT] = {};
    double doubleBuffer[ROW_COUNT] = {};
    char dateBuffer[ROW_COUNT][100] = {"27-JUN-2020","29-AUG-1992"};

    //int buffer[ROW_COUNT]={100};

    for(int i=0;i<ROW_COUNT;i++)
    {
        strcpy(strBuffer[i], string("STR_COLUMN_"+to_string(i)).c_str());
        intBuffer[i]=i;
        doubleBuffer[i]=2+0.89;
    }
        
    static text *insertstr = (text *)"INSERT INTO V6Play (MyVarchar,MyNumber,MyNumber2,MyDate) VALUES (:1,:2,:3,:4)";
    //static text *insertstr = (text *)"INSERT INTO V6Play1 (MyNumber) VALUES (:1)";

std::cout << " \n==============V6P: TEXT_AND_VALUE "<<  2  << "==================" << std::endl;

    //Allocate session handle
    IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&stmthp, (ub4)OCI_HTYPE_STMT, (size_t)0, (dvoid **)0));

        std::cout << " \n==============V6P: TEXT_AND_VALUE "<<  3  << "==================" << std::endl;

    IS_ERROR(pOciErrorHandle, OCIStmtPrepare(stmthp, pOciErrorHandle, insertstr,
                                             strlen((char *)insertstr),
                                             (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT));

        std::cout << " \n==============V6P: TEXT_AND_VALUE "<<  3.3  << "==================" << std::endl;

    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 1, strBuffer[0],
                                           sizeof(strBuffer[0]), SQLT_STR,
                                           indicatorForColumn1, NULL, NULL, 0,
                                           (ub4 *)0, OCI_DEFAULT));
    
    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 2, intBuffer,
                                           sizeof(intBuffer[0]), SQLT_INT,
                                           NULL, NULL, NULL, 0,
                                           (ub4 *)0, OCI_DEFAULT));
    
    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 3, doubleBuffer,
                                           sizeof(doubleBuffer[0]), SQLT_FLT,
                                           NULL, NULL, NULL, 0,
                                           (ub4 *)0, OCI_DEFAULT));

    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 4, dateBuffer,
                                           sizeof(dateBuffer[0]), SQLT_STR,
                                           NULL, NULL, NULL, 0,
                                           (ub4 *)0, OCI_DEFAULT));

    // IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 1, &buffer[0],
    //                                        sizeof(buffer[0]), SQLT_INT ,
    //                                        indicatorForColumn1, (ub2 *)0, (ub2 *)0, 0,
    //                                        (ub4 *)0, OCI_DEFAULT));

    //OCIBindArrayOfStruct(ociBind, pOciErrorHandle, sizeof(int),indicatorForColumn1[0], LegthForColumn1[0], returnCodeForColumn1[0]);
        std::cout << " \n==============V6P: TEXT_AND_VALUE "<< 5   << "==================" << std::endl;

    IS_ERROR(pOciErrorHandle, OCIStmtExecute(pOciServiceContextHandle, stmthp, pOciErrorHandle, ROW_COUNT, 0,
                                             (OCISnapshot *)0, (OCISnapshot *)0, OCI_DEFAULT));

        std::cout << " \n==============V6P: TEXT_AND_VALUE "<<  6  << "==================" << std::endl;

    IS_ERROR(pOciErrorHandle,OCITransCommit (pOciServiceContextHandle,pOciErrorHandle,OCI_DEFAULT));

    return 0;
}




void connectToDb(long long int handleId)
{
    OCIConnection ociConnection;

    if (0 != ociConnection.connectToDb(handleId))
		return ;

        if (0 != ociConnection.insertToTable())
        return ;
   
}

int fetch(long long int handleId)
{
    
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

