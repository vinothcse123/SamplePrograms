
//g++ $1 -std=c++11 -I $ORACLE_HOME/rdbms/public/ -L $ORACLE_HOME/lib/  -lclntsh

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

int OCIConnection::insertToTable()
{
    const int ROW_COUNT = 9;
    const int COLUMN_COUNT = 9;
    OCIStmt *stmthp = (OCIStmt *)0;
    OCIBind *ociBind = (OCIBind *)0;

    short indicatorForColumn1[COLUMN_COUNT]; /* indicators */
    ub4 LegthForColumn1[COLUMN_COUNT];       /* return lengths */
    ub2 returnCodeForColumn1[COLUMN_COUNT];  /* return codes */

    char buffer[ROW_COUNT][100] = {};

    //int buffer[ROW_COUNT]={100};

    strcpy(buffer[0], "PAVAN KARTHI GV");
    strcpy(buffer[1], "VINOTH KUMAR GANESAN");
    strcpy(buffer[2], "KIRUBA SUBRAMANI");

    static text *insertstr = (text *)"INSERT INTO V6Play (MyVarchar) VALUES (:1)";
    //static text *insertstr = (text *)"INSERT INTO V6Play (MyNumber) VALUES (:1)";

    //Allocate session handle
    IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&stmthp, (ub4)OCI_HTYPE_STMT, (size_t)0, (dvoid **)0));

    IS_ERROR(pOciErrorHandle, OCIStmtPrepare(stmthp, pOciErrorHandle, insertstr,
                                             strlen((char *)insertstr),
                                             (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT));


    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 1, buffer[0],
                                           sizeof(buffer[0]), SQLT_STR,
                                           (void *)indicatorForColumn1, (ub2 *)0, (ub2 *)returnCodeForColumn1, 0,
                                           (ub4 *)0, OCI_DEFAULT));

    // IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 1, &buffer[0],
    //                                        sizeof(buffer[0]), SQLT_INT ,
    //                                        (ub2 *)0, (ub2 *)0, (ub2 *)0, 0,
    //                                        (ub4 *)0, OCI_DEFAULT));

    //OCIBindArrayOfStruct(ociBind, pOciErrorHandle, sizeof(int),indicatorForColumn1[0], LegthForColumn1[0], returnCodeForColumn1[0]);

    IS_ERROR(pOciErrorHandle, OCIStmtExecute(pOciServiceContextHandle, stmthp, pOciErrorHandle, ROW_COUNT, 0,
                                             (OCISnapshot *)0, (OCISnapshot *)0, OCI_COMMIT_ON_SUCCESS));

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
