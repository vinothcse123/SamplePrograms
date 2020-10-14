
#include <iostream>
#include <dpi.h>
#include <cstring>
#include <string>

#define MAJOR_VERSION 4
#define MINOR_VERSION 1

using std::string;

dpiContext *pContext = NULL;
dpiConn *conn;

int dpiSamples_showError(void)
{
    dpiErrorInfo info;

    dpiContext_getError(pContext, &info);
    fprintf(stderr, "ERROR: %.*s (%s: %s), offset: %u\n", info.messageLength,
            info.message, info.fnName, info.action, info.offset);
    return -1;
}

void connectToDb()
{
    string userName = "userName", password = "userName", dbName = "userName";
    dpiErrorInfo errorInfo;

    if (dpiContext_createWithParams(MAJOR_VERSION, MINOR_VERSION,
                                    NULL, &pContext, &errorInfo) < 0)
    {
        fprintf(stderr, "ERROR: %.*s (%s : %s)\n", errorInfo.messageLength,
                errorInfo.message, errorInfo.fnName, errorInfo.action);
    }

    if (dpiConn_create(pContext, userName.c_str(),
                       userName.length(), password.c_str(),
                       password.length(), dbName.c_str(),
                       dbName.length(), NULL, NULL, &conn) < 0)
    {
        dpiErrorInfo info;
        dpiContext_getError(pContext, &info);
        fprintf(stderr, "ERROR: %.*s (%s: %s), offset: %u\n", info.messageLength,
                info.message, info.fnName, info.action, info.offset);
    }
}

int fetch()
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

int main()
{
    connectToDb();
    fetch();
    return 0;
}
