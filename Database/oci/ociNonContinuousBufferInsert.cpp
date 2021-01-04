
//GH_DB_ORA_2

//g++ $1 -std=c++11 -I $ORACLE_HOME/rdbms/public/ -L $ORACLE_HOME/lib/  -lclntsh

#include <iostream>
#include <oci.h>
#include <string>
#include <cstring>
#include <chrono>

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
    const int ROW_COUNT = 2;
    const int BUFFER_1_SIZE = 1;
    const int BUFFER_2_SIZE = 1;
    const int NUMBER_OF_BUFFERS = 2;
    const int STRING_LENGTH = 100;
    const int DATE_LENTH_USING_DAT_TYPE = 7;

    OCIStmt *stmthp = (OCIStmt *)0;
    OCIBind *ociBind = (OCIBind *)0;

    sb2 indicatorForColumn1[ROW_COUNT]={0,0}; /* indicators - passing value as -1, inserts null for row*/  
    ub2 LegthForColumn1[ROW_COUNT]={5,20};   /* return lengths */
    ub2 LegthForDateColumn[ROW_COUNT];   /* return lengths */
    ub2 returnCodeForColumn1[ROW_COUNT]={0};  /* return codes */

    char strBuffer_1[BUFFER_1_SIZE][STRING_LENGTH] = {};
    char strBuffer_2[BUFFER_2_SIZE][STRING_LENGTH] = {};
    int intBuffer_1[BUFFER_1_SIZE] = {};
    int intBuffer_2[BUFFER_2_SIZE] = {};
    double doubleBuffer[ROW_COUNT] = {};
    char dateBuffer[ROW_COUNT][STRING_LENGTH] = {"27-JUN-2020"};
    char dateBufferUsingDateType[ROW_COUNT][DATE_LENTH_USING_DAT_TYPE];

    OCIIOV  ioVecInt[NUMBER_OF_BUFFERS],ioVecStr[NUMBER_OF_BUFFERS],ioVecFloat[NUMBER_OF_BUFFERS],ioVecDate[ROW_COUNT],ioVecDateUsingDateType[ROW_COUNT];

    for (int i = 0; i < ROW_COUNT; i++)
    {
        doubleBuffer[i] = 2 + 0.89;
        LegthForDateColumn[i] = 11; //11 is legnth of "27-JUN-2020"
        strcpy(dateBuffer[i], "27-JUN-2020");
        ioVecDate[i].bfp = dateBuffer[i];
        ioVecDate[i].bfl = sizeof(dateBuffer[i]);

        struct tm *tm;
        time_t time_of_elem;

        // get the current time
        const auto now = std::chrono::system_clock::now();

        // transform the time into a duration since the epoch
        const auto epoch = now.time_since_epoch();

        // cast the duration into seconds
        const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);

        time_of_elem = (time_t)seconds.count();
        tm = localtime(&time_of_elem);
        dateBufferUsingDateType[i][0] = (tm->tm_year + 1900) / 100 + 100; // century
        dateBufferUsingDateType[i][1] = (tm->tm_year % 100) + 100;        // year
        dateBufferUsingDateType[i][2] = tm->tm_mon + 1;                   // month
        dateBufferUsingDateType[i][3] = tm->tm_mday;                      // day
        dateBufferUsingDateType[i][4] = tm->tm_hour + 1;                  // hour
        dateBufferUsingDateType[i][5] = tm->tm_min + 1;                   // min
        dateBufferUsingDateType[i][6] = tm->tm_sec + 1;                   // sec

        ioVecDateUsingDateType[i].bfp = dateBufferUsingDateType[i];
        ioVecDateUsingDateType[i].bfl = DATE_LENTH_USING_DAT_TYPE;
    }

    for(int i=0;i<BUFFER_1_SIZE;i++)
    {
        intBuffer_1[i]=100+i;
        strcpy(strBuffer_1[i], string("STR_COLUMN_"+to_string(100+i)).c_str());
    }

    for(int i=0;i<BUFFER_2_SIZE;i++)
    {
        intBuffer_2[i]=200+i;
        strcpy(strBuffer_2[i], string("STR_COLUMN_"+to_string(200+i)).c_str());
    }
        
    static text *insertstr = (text *)"INSERT INTO V6Play (MyNumber,MyVarchar,MyNumber2,Mydate) VALUES (:1,:2,:3,:4)";
    //static text *insertstr = (text *)"INSERT INTO V6Play (MyNumber) VALUES (:1)";

    //Allocate session handle
    IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&stmthp, (ub4)OCI_HTYPE_STMT, (size_t)0, (dvoid **)0));

    IS_ERROR(pOciErrorHandle, OCIStmtPrepare(stmthp, pOciErrorHandle, insertstr,
                                             strlen((char *)insertstr),
                                             (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT));


    

    ioVecInt[0].bfp=intBuffer_1;
    ioVecInt[0].bfl=BUFFER_1_SIZE*sizeof(intBuffer_1[0]);
    ioVecInt[1].bfp=intBuffer_2;
    ioVecInt[1].bfl=BUFFER_2_SIZE*sizeof(intBuffer_2[0]);
    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 1,(void *) &ioVecInt,
                                           sizeof(intBuffer_1[0]), SQLT_INT,
                                           NULL, NULL, NULL, 0,
                                           (ub4 *)0, OCI_IOV));      

    ioVecStr[0].bfp=strBuffer_1;
    ioVecStr[0].bfl=BUFFER_1_SIZE*sizeof(strBuffer_1[0]);;
    ioVecStr[1].bfp=strBuffer_2;
    ioVecStr[1].bfl=BUFFER_2_SIZE*sizeof(strBuffer_2[0]);
    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 2,(void*) &ioVecStr,
                                           sizeof(strBuffer_1[0]), SQLT_CHR,
                                           indicatorForColumn1, LegthForColumn1, NULL, 0,
                                           (ub4 *)0, OCI_IOV));                              

    ioVecFloat[0].bfp=doubleBuffer;
    ioVecFloat[0].bfl=ROW_COUNT*sizeof(doubleBuffer[0]);
    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 3, (void*)ioVecFloat,
                                           sizeof(doubleBuffer[0]), SQLT_FLT,
                                           NULL, NULL, NULL, 0,
                                           (ub4 *)0, OCI_IOV));
    
    // Using string format by SQLT_STR

    //  IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 4,(void*) &ioVecDate,
    //                                        sizeof(dateBuffer[0]), SQLT_STR,
    //                                        NULL, NULL, NULL, 0,
    //                                        (ub4 *)0, OCI_IOV)); 

    // Using encoded date format by SQLT_DAT
    IS_ERROR(pOciErrorHandle, OCIBindByPos(stmthp, &ociBind, pOciErrorHandle, 4,(void*) &ioVecDateUsingDateType,
                                           sizeof(dateBufferUsingDateType[0]), SQLT_DAT,
                                           NULL, NULL, NULL, 0,
                                           (ub4 *)0, OCI_IOV)); 
 

    IS_ERROR(pOciErrorHandle, OCIStmtExecute(pOciServiceContextHandle, stmthp, pOciErrorHandle, ROW_COUNT, 0,
                                             (OCISnapshot *)0, (OCISnapshot *)0, OCI_DEFAULT));


    int rowsLoaded =-1;

    OCIAttrGet( stmthp, OCI_HTYPE_STMT, (void*)&rowsLoaded, NULL, OCI_ATTR_ROWS_FETCHED, pOciErrorHandle );

    std::cout << " \n==============V6P: rowsLoaded :  "<<  rowsLoaded  << " ==================" << std::endl;



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
