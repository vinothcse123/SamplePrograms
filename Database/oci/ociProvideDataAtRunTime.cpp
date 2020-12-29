

//g++ $1 -std=c++11 -I $ORACLE_HOME/rdbms/public/ -L $ORACLE_HOME/lib/  -lclntsh
// This will provide data at runtime using callback function registered.

#include <iostream>
#include <oci.h>
#include <string>
#include <cstring>

using namespace std;

class OCIConnection
{
public:
    //V6P
    //string schemaNameStr = "schemaNameStr", userStr = "userStr", passwordStr = "passwordStr";
    OCIEnv *pOciEnv;
    OCIError *pOciErrorHandle;
    OCISvcCtx *pOciServiceContextHandle = nullptr;
    sword ociret; /* return code from OCI calls */
    ub2 id_col;
    OCIServer *pOciServerHandle = nullptr;
    OCISession *pOciSessionHandle = nullptr;

    int connectToDb();
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

int OCIConnection::connectToDb()
{
    //Create Environment

    if (OCIEnvCreate((OCIEnv **)&pOciEnv, (ub4)OCI_DEFAULT,
                     (dvoid *)0, (dvoid * (*)(dvoid *, size_t))0,
                     (dvoid * (*)(dvoid *, dvoid *, size_t))0,
                     (void (*)(dvoid *, dvoid *))0, (size_t)0, (dvoid **)0))
    {
        std::cout << " \n==============V6P: Unabled to create Environment==================" << std::endl;
        return -1;
    }

    // Set error handler

    IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciErrorHandle, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0));

    // set server handle

    IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciServerHandle, OCI_HTYPE_SERVER, (size_t)0, (dvoid **)0));

    //set service handle

    IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciServiceContextHandle, OCI_HTYPE_SVCCTX, (size_t)0, (dvoid **)0));

    //Connect to server

    IS_ERROR(pOciErrorHandle, OCIServerAttach(pOciServerHandle, pOciErrorHandle, (text *)schemaNameStr.c_str(), (sb4)schemaNameStr.length(), (ub4)OCI_DEFAULT));

    //set server context

    IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciServiceContextHandle, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)pOciServerHandle, (ub4)0, (ub4)OCI_ATTR_SERVER, (OCIError *)pOciErrorHandle));

    //Allocate session handle
    IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (size_t)0, (dvoid **)0));

    // Set the username
    IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)userStr.c_str(), (ub4)userStr.length(), (ub4)OCI_ATTR_USERNAME, pOciErrorHandle));

    // Set the password
    IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)passwordStr.c_str(), (ub4)passwordStr.length(), (ub4)OCI_ATTR_PASSWORD, pOciErrorHandle));

    // Set the schema attribute
    IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)userStr.c_str(), (ub4)userStr.length(), (ub4)OCI_ATTR_CURRENT_SCHEMA, pOciErrorHandle));

    //Begin the session
    IS_ERROR(pOciErrorHandle, OCISessionBegin(pOciServiceContextHandle, pOciErrorHandle, pOciSessionHandle, OCI_CRED_RDBMS, (ub4)OCI_DEFAULT));

    // set session parameters for authentication
    IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciServiceContextHandle, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)pOciSessionHandle, (ub4)0, (ub4)OCI_ATTR_SESSION, pOciErrorHandle));

    return 0;
}

int32_t g_int =300;
string g_string = "STRING_COLUMN";

static sb4 callBackFunctionIn(dvoid *ctxp, OCIBind *bindp, ub4 iter, ub4 index,
                      dvoid **bufpp, ub4 *alenpp, ub1 *piecep, dvoid **indpp)
{
    ub4    pos = *((ub4 *)ctxp);
    std::cout << " \n============== V6P: Inputs "<<"Pos:  "<< pos <<", Iter:"<< iter  <<", Index:"<< index<< std::endl;

if(pos == 0) // FIRST COLUMN
{
  *bufpp = (dvoid *)&g_int;
  *alenpp = sizeof(int32_t);
  *indpp = (dvoid *) 0;
}
else if(pos == 1) // SECOND COLUMN
{
    *bufpp = (dvoid *)g_string.c_str();
  *alenpp = g_string.length();
  *indpp = (dvoid *) 0;
}

  

  *piecep = OCI_ONE_PIECE;
  return OCI_CONTINUE;
}


/* ----------------------------------------------------------------- */
/* Outbind callback for returning data.                              */
/* ----------------------------------------------------------------- */
static sb4 callBackFunctionOut(dvoid *ctxp, OCIBind *bindp, ub4 iter, ub4 index,
                         dvoid **bufpp, ub4 **alenp, ub1 *piecep,
                         dvoid **indpp, ub2 **rcodepp)
{
    std::cout << " \n============== V6P: callBackFunctionOut ==================" << std::endl;


  return OCI_CONTINUE;
}



int OCIConnection::insertToTable()
{
    const int ROW_COUNT = 5;
    const int COL_COUNT = 2;
    const int STRING_LEN = 100;
    OCIStmt *stmthp = (OCIStmt *)0;
    OCIBind *ociBindArr[COL_COUNT]; 
    int pos[COL_COUNT];

    for(int i=0;i<COL_COUNT;i++)
        pos[i]=i;

    sb2 indicatorForColumn1[ROW_COUNT]={-1,0,0}; /* indicators - passing value as -1, inserts null for row*/  
    ub2 LegthForColumn1[ROW_COUNT]={3};       /* return lengths */
    ub2 returnCodeForColumn1[ROW_COUNT]={0};  /* return codes */

    char strBuffer[ROW_COUNT][STRING_LEN] = {};
    int intBuffer[ROW_COUNT] = {};
    double doubleBuffer[ROW_COUNT] = {};

    //int buffer[ROW_COUNT]={100};

    for(int i=0;i<ROW_COUNT;i++)
    {
        strcpy(strBuffer[i], string("STR_COLUMN_"+to_string(i)).c_str());
        intBuffer[i]=i;
        doubleBuffer[i]=2+0.89;
    }
        
    static text *insertstr = (text *)"INSERT INTO V6Play1 (MyNumber,MyVarchar) VALUES (:1,:2)";
    //static text *insertstr = (text *)"INSERT INTO V6Play1 (MyNumber) VALUES (:1)";

    //Allocate session handle
    IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&stmthp, (ub4)OCI_HTYPE_STMT, (size_t)0, (dvoid **)0));

    IS_ERROR(pOciErrorHandle, OCIStmtPrepare(stmthp, pOciErrorHandle, insertstr,
                                             strlen((char *)insertstr),
                                             (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT));


    
    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBindArr[0], pOciErrorHandle, 1, NULL,
                                           sizeof(intBuffer[0]), SQLT_INT,
                                           NULL, NULL, NULL, 0,
                                           (ub4 *)0, OCI_DATA_AT_EXEC ));


    IS_ERROR(pOciErrorHandle, OCIBindDynamic (ociBindArr[0],pOciErrorHandle,(dvoid *)&pos[0],callBackFunctionIn, (dvoid *)&pos[0],callBackFunctionOut));

    //Second column

    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBindArr[1], pOciErrorHandle, 2, NULL,
                                           STRING_LEN, SQLT_CHR,
                                           NULL, NULL, NULL, 0,
                                           (ub4 *)0, OCI_DATA_AT_EXEC ));

    

    IS_ERROR(pOciErrorHandle, OCIBindDynamic (ociBindArr[1],pOciErrorHandle,(dvoid *)&pos[1],callBackFunctionIn, (dvoid *)&pos[1],callBackFunctionOut));
    

    IS_ERROR(pOciErrorHandle, OCIStmtExecute(pOciServiceContextHandle, stmthp, pOciErrorHandle, ROW_COUNT, 0,
                                             (OCISnapshot *)0, (OCISnapshot *)0, OCI_DEFAULT));


    IS_ERROR(pOciErrorHandle,OCITransCommit (pOciServiceContextHandle,pOciErrorHandle,OCI_DEFAULT));

    return 0;
}

int main()
{
    OCIConnection ociConnection;

    if (0 != ociConnection.connectToDb())
        return -1;

    if (0 != ociConnection.insertToTable())
        return -1;
}
